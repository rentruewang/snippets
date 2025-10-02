/// Copyright (c) RenChu Wang - All Rights Reserved

#include <cassert>
#include <chrono>
#include <cstdlib>
#include <exception>
#include <future>
#include <iostream>
#include <memory>
#include <numeric>
#include <semaphore>
#include <sstream>
#include <stdexcept>
#include <thread>
#include <vector>

using namespace std;

// The compute class, with couple of members, representing differnt operations.
class compute : enable_shared_from_this<compute> {
   public:
    compute() : call_count_(0) {}
    virtual ~compute() {}
    virtual int eval() = 0;
    virtual vector<shared_ptr<compute>> children() const = 0;
    virtual string str() const = 0;

    int operator()() {
        ++call_count_;
        cout << this->str() << "\n";
        return eval();
    }

    size_t cnt() const { return call_count_; }

   private:
    size_t call_count_;
};
namespace {
class semaphore_guard {
   public:
    semaphore_guard(counting_semaphore<>& sem, const string& by)
        : sem_(sem), by_(by) {
        cout << "acq(" << by_ << ")\n";
        sem_.acquire();
    }
    ~semaphore_guard() {
        cout << "rel(" << by_ << ")\n";
        sem_.release();
    }

   private:
    // This is guarenteed to be alive, so using a reference.
    counting_semaphore<>& sem_;
    string by_;
};
}  // namespace
// The semaphore class. Simulate a fixed amount of resources (threads).
class sema {
   protected:
    // Using a reference s.t. the semaphore don't get copied.
    sema(counting_semaphore<>& sem) : sem_(sem) {}
    semaphore_guard acquire(const string& by) {
        // Using copy elision, to avoid acquiring and releasing and acquiring.
        return semaphore_guard(sem_, by);
    }

   private:
    counting_semaphore<>& sem_;
};

class literal : public compute {
   public:
    literal(int i) : data_(i) {}
    int eval() override { return data_; }
    vector<shared_ptr<compute>> children() const override { return {}; }
    string str() const override {
        stringstream out;
        out << data_;
        return out.str();
    }

   private:
    int data_;
};

class summation : public compute {
   public:
    summation(vector<shared_ptr<compute>> op) : operands_(op) {}

    int eval() override {
        int summation = 0;
        for (auto op : operands_) {
            summation += (*op)();
        }
        return summation;
    }

    vector<shared_ptr<compute>> children() const override { return operands_; }
    string str() const override {
        stringstream out;
        for (size_t i = 0; i < operands_.size(); ++i) {
            out << operands_[i]->str();

            if (i != operands_.size() - 1) {
                out << " + ";
            }
        }
        return out.str();
    }

   private:
    vector<shared_ptr<compute>> operands_;
};

class product : public compute {
   public:
    product(vector<shared_ptr<compute>> op) : operands_(op) {}

    int eval() override {
        int product = 1;
        for (auto op : operands_) {
            product *= (*op)();
        }
        return product;
    }

    vector<shared_ptr<compute>> children() const override { return operands_; }
    string str() const override {
        stringstream out;
        for (size_t i = 0; i < operands_.size(); ++i) {
            out << operands_[i]->str();

            if (i != operands_.size() - 1) {
                out << " * ";
            }
        }
        return out.str();
    }

   private:
    vector<shared_ptr<compute>> operands_;
};

class cache : public compute {
   public:
    cache(shared_ptr<compute> op) : operand_(op) {}

    int eval() override {
        if (value_ >= 0) {
            return value_;
        }

        value_ = (*operand_)();
        return value_;
    }

    vector<shared_ptr<compute>> children() const override { return {operand_}; }
    string str() const override {
        stringstream out;
        out << "c(" << operand_->str() << ")";
        return out.str();
    }

   private:
    shared_ptr<compute> operand_;
    int value_ = -1;
};

// Task classes are like `Task` in python,
// where execution starts immediately,
// but depends on other `Task`s,
// so this means that recursively triggering the tasks can cause a deadlock,
// due to the limited budget smaller than the dependencies.
// For example, when budget = 1, a depending on b,
// a would require a thread to run, and then b would require a thread to run,
// exceeding the budget (a runs first before b).
class task_literal : public literal, sema {
   public:
    task_literal(int i, counting_semaphore<>& sem) : literal(i), sema(sem) {}

    int eval() override {
        auto sem{acquire("task_lit_" + str())};
        return literal::eval();
    }
};
class task_summation : public summation, sema {
   public:
    task_summation(vector<shared_ptr<compute>> op, counting_semaphore<>& sem)
        : summation(op), sema(sem) {}

    int eval() override {
        auto sem{acquire("task_sum_" + str())};
        return summation::eval();
    }
};

// Lazy classes doesn't cause deadlocks,
// because they are reduced from the leaves of the expression tree,
// which can be linearly ordered (no deadlock so long as semaphore > 1).
class lazy_literal : public literal, sema {
   public:
    lazy_literal(int i, counting_semaphore<>& sem) : literal(i), sema(sem) {}
    int eval() override {
        // As literal has no children, this can be the same as `literal_task`.
        auto sem{acquire("lazy_lit_" + str())};
        return literal::eval();
    }
};
class lazy_summation : public summation, sema {
   public:
    lazy_summation(vector<shared_ptr<compute>> op, counting_semaphore<>& sem)
        : summation(op), sema(sem) {}
    int eval() override {
        vector<int> values;

// Using omp parallel to simulate multiple threads.
#pragma omp parallel for
        for (auto child : children()) {
#pragma omp critical
            values.push_back(((*child)()));
        }

        // Only acquiring when needed.
        // Previous I put this into the for loop, before the child call,
        // but this just means that we are acquiring twice for the child call,
        // and none for the current call.
        auto sem{acquire("lazy_sum_" + str())};
        return accumulate(values.begin(), values.end(), 0);
    }
};

void raise_error_on_deadlock(counting_semaphore<>& sem, future<string> fut) {
    for (;;) {
        if (!sem.try_acquire()) {
            throw runtime_error("--- deadlock! ---");
        }

        if (fut.wait_for(chrono::seconds(0)) == future_status::ready) {
            return;
        }

        // Lock is acquired.
        cout << "Acquired in deadlock detection. No deadlock\n";
        sem.release();
        this_thread::sleep_for(chrono::seconds(1));
    }
}

class deadlock_detection_guard {
   public:
    deadlock_detection_guard(size_t count)
        : sem_(counting_semaphore<>(count)), prom_(promise<string>()) {
        th_ = thread(raise_error_on_deadlock, ref(sem_), prom_.get_future());
    }

    void cancel() {
        prom_.set_value("done");
        th_.join();
        cout << "Thread is being cancelled...\n";
    }
    counting_semaphore<>& sema() { return sem_; }

    ~deadlock_detection_guard() { cancel(); }

   private:
    counting_semaphore<> sem_;
    thread th_;
    promise<string> prom_;
};

int main() {
    using expr = shared_ptr<compute>;
    expr one, two, three, sum_six, prod_six, twelve, thrity_six;
    vector<expr> one_two_three, six_six;

    cout << "---- Normal section ----\n";
    {
        one = make_shared<literal>(1);
        two = make_shared<literal>(2);
        three = make_shared<literal>(3);

        one_two_three = {one, two, three};
        sum_six = make_shared<summation>(one_two_three);
        prod_six = make_shared<product>(one_two_three);

        // Too lazy to implemen cache / product for lazy / task.
        expr cache_sum_six = make_shared<cache>(sum_six);
        expr cache_prod_six = make_shared<cache>(prod_six);

        six_six = {cache_sum_six, cache_prod_six};

        twelve = make_shared<summation>(six_six);
        thrity_six = make_shared<product>(six_six);

        assert((*one)() == 1);
        assert((*two)() == 2);
        assert((*three)() == 3);
        assert((*sum_six)() == 6);
        assert((*prod_six)() == 6);
        assert((*cache_sum_six)() == 6);
        assert((*cache_prod_six)() == 6);
        assert((*twelve)() == 12);
        assert((*thrity_six)() == 36);
        assert(sum_six->cnt() == 2);
        assert(prod_six->cnt() == 2);

        cout << "twelve = " << (*twelve)() << "\n";
        cout << "thrity_six = " << (*thrity_six)() << "\n";
        cout << "Done normal\n";
    }
    cout << "\n\n\n\n";

    cout << "---- Lazy section ----\n";
    {
        deadlock_detection_guard sdd(1);
        one = make_shared<lazy_literal>(1, sdd.sema());
        two = make_shared<lazy_literal>(2, sdd.sema());
        three = make_shared<lazy_literal>(3, sdd.sema());

        one_two_three = {one, two, three};
        sum_six = make_shared<lazy_summation>(one_two_three, sdd.sema());
        six_six = {sum_six, sum_six};
        twelve = make_shared<lazy_summation>(six_six, sdd.sema());
        assert((*twelve)() == 12);
        cout << "Done lazy\n";
    }
    cout << "\n\n\n\n";

    cout << "---- Task section ----\n";
    {
        deadlock_detection_guard sdd(1);
        one = make_shared<task_literal>(1, sdd.sema());
        two = make_shared<task_literal>(2, sdd.sema());
        three = make_shared<task_literal>(3, sdd.sema());

        one_two_three = {one, two, three};
        sum_six = make_shared<task_summation>(one_two_three, sdd.sema());
        six_six = {sum_six, sum_six};
        twelve = make_shared<task_summation>(six_six, sdd.sema());
        assert((*twelve)() == 12);

        // Impossible to achieve.
        cout << "Done deadlock\n";
    }
    cout << "\n\n\n\n";
}
