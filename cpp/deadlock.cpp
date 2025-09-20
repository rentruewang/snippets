/// Copyright (c) RenChu Wang - All Rights Reserved

#include <cassert>
#include <chrono>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>
#include <numeric>
#include <semaphore>
#include <sstream>
#include <thread>
#include <vector>

using namespace std;

// The compute class, with couple of members, representing differnt operations.
class compute : enable_shared_from_this<compute> {
   public:
    compute() : call_count_(0) {}
    virtual ~compute() {}
    virtual int get() = 0;
    virtual vector<shared_ptr<compute>> children() const = 0;
    virtual string str() const = 0;

    int operator()() {
        ++call_count_;
        cout << this->str() << "\n";
        return get();
    }

    size_t cnt() const { return call_count_; }

   private:
    size_t call_count_;
};

class scoped_semaphore {
   public:
    scoped_semaphore(counting_semaphore<>& sem, const string& by)
        : sem_(sem), by_(by) {
        cout << "acq(" << by_ << ")\n";
        sem_.acquire();
    }
    ~scoped_semaphore() {
        cout << "rel(" << by_ << ")\n";
        sem_.release();
    }

   private:
    // This is guarenteed to be alive, so using a reference.
    counting_semaphore<>& sem_;
    string by_;
};
// The semaphore class. Simulate a fixed amount of resources (threads).
class sema {
   protected:
    // Using a reference s.t. the semaphore don't get copied.
    sema(counting_semaphore<>& sem) : sem_(sem) {}
    scoped_semaphore acquire_semaphore(string by) {
        // Using copy elision, to avoid acquiring and releasing and acquiring.
        return scoped_semaphore(sem_, by);
    }

   private:
    counting_semaphore<>& sem_;
};

class literal : public compute {
   public:
    literal(int i) : data_(i) {}
    int get() override { return data_; }
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

    int get() override {
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

    int get() override {
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
    cache(shared_ptr<compute> op) : operand(op) {}

    int get() override {
        if (value_ >= 0) {
            return value_;
        }

        value_ = (*operand)();
        return value_;
    }

    vector<shared_ptr<compute>> children() const override { return {operand}; }
    string str() const override {
        stringstream out;
        out << "c(" << operand->str() << ")";
        return out.str();
    }

   private:
    shared_ptr<compute> operand;
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

    int get() override {
        auto sem{acquire_semaphore("task_lit_" + str())};
        return literal::get();
    }
};
class task_summation : public summation, sema {
   public:
    task_summation(vector<shared_ptr<compute>> op, counting_semaphore<>& sem)
        : summation(op), sema(sem) {}

    int get() override {
        auto sem{acquire_semaphore("task_sum_" + str())};
        return summation::get();
    }
};

// Lazy classes doesn't cause deadlocks,
// because they are reduced from the leaves of the expression tree,
// which can be linearly ordered (no deadlock so long as semaphore > 1).
class lazy_literal : public literal, sema {
   public:
    lazy_literal(int i, counting_semaphore<>& sem) : literal(i), sema(sem) {}
    int get() override {
        // As literal has no children, this can be the same as `literal_task`.
        auto sem{acquire_semaphore("lazy_lit_" + str())};
        return literal::get();
    }
};
class lazy_summation : public summation, sema {
   public:
    lazy_summation(vector<shared_ptr<compute>> op, counting_semaphore<>& sem)
        : summation(op), sema(sem) {}
    int get() override {
        vector<int> values;

// Uisng omp parallel to simulate multiple threads.
#pragma omp parallel for
        for (auto child : children()) {
#pragma omp critical
            values.push_back(((*child)()));
        }

        // Only acquiring when needed.
        // Previous I put this into the for loop, before the child call,
        // but this just means that we are acquiring twice for the child call,
        // and none for the current call.
        auto sem{acquire_semaphore("lazy_sum_" + str())};
        return accumulate(values.begin(), values.end(), 0);
    }
};

void raise_error_on_deadlock(counting_semaphore<>& sem) {
    for (;;) {
        if (!sem.try_acquire()) {
            cout << "--- deadlock! ---\n";
            abort();
        }

        // Lock is acquired.
        cout << "Acquired in deadlock detection. No deadlock\n";
        sem.release();
        this_thread::sleep_for(chrono::seconds(3));
    }
}

class scoped_deadlock_detection {
   public:
    scoped_deadlock_detection(counting_semaphore<>& sem)
        : sem_(sem), th_(thread(raise_error_on_deadlock, ref(sem))) {}

    ~scoped_deadlock_detection() { th_.join(); }

   private:
    counting_semaphore<>& sem_;
    thread th_;
};
int main() {
    using expr = shared_ptr<compute>;
    expr one, two, three, sum_six, prod_six, twelve, thrity_six;
    vector<expr> one_two_three, six_six;

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
        cout << "Done normal\n\n\n\n";
    }

    counting_semaphore<> sem(1);
    scoped_deadlock_detection sdd(sem);
    {
        one = make_shared<lazy_literal>(1, sem);
        two = make_shared<lazy_literal>(2, sem);
        three = make_shared<lazy_literal>(3, sem);

        one_two_three = {one, two, three};
        sum_six = make_shared<lazy_summation>(one_two_three, sem);
        six_six = {sum_six, sum_six};
        twelve = make_shared<lazy_summation>(six_six, sem);
        assert((*twelve)() == 12);
        cout << "Done lazy\n\n\n\n";
    }

    {
        one = make_shared<task_literal>(1, sem);
        two = make_shared<task_literal>(2, sem);
        three = make_shared<task_literal>(3, sem);

        one_two_three = {one, two, three};
        sum_six = make_shared<task_summation>(one_two_three, sem);
        six_six = {sum_six, sum_six};
        twelve = make_shared<task_summation>(six_six, sem);
        assert((*twelve)() == 12);

        // Impossible to achieve.
        cout << "Done deadlock\n";
    }
}
