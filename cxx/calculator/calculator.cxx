#include "calculator.hxx"

#include <fmt/core.h>

shared_ptr<Expression> Expression::Add(
    const shared_ptr<Expression>& other) const {
    return make_unique<Evaluation>(shared_from_this(), other, "+",
                                   [](int a, int b) { return a + b; });
}

shared_ptr<Expression> Expression::Sub(
    const shared_ptr<Expression>& other) const {
    return make_unique<Evaluation>(shared_from_this(), other, "-",
                                   [](int a, int b) { return a - b; });
}

shared_ptr<Expression> Expression::Mul(
    const shared_ptr<Expression>& other) const {
    return make_unique<Evaluation>(shared_from_this(), other, "*",
                                   [](int a, int b) { return a * b; });
}

Expression::~Expression() {}

Literal::Literal(int data) : data_(data) {}

shared_ptr<const Expression> Literal::simplify() const {
    return shared_from_this();
}

string Literal::to_string() const {
    return fmt::format("{}", data_);
}

int Literal::data() const {
    return data_;
}

Literal::~Literal() {}

Variable::Variable(string data) : data_(data) {}

shared_ptr<const Expression> Variable::simplify() const {
    return shared_from_this();
}

string Variable::to_string() const {
    return data_;
}

Variable::~Variable() {}

Evaluation::Evaluation(shared_ptr<const Expression> left,
                       shared_ptr<const Expression> right,
                       string token,
                       function<int(int, int)> func)
    : left_(left), right_(right), token_(token), func_(func) {}

shared_ptr<const Expression> Evaluation::simplify() const {
    auto lp = dynamic_pointer_cast<const Literal>(left_->simplify());
    auto rp = dynamic_pointer_cast<const Literal>(right_->simplify());

    // Do nothing because no simplification is needed.
    if (lp == nullptr || rp == nullptr) {
        return shared_from_this();
    }

    return make_shared<Literal>(func_(lp->data(), rp->data()));
}

string Evaluation::to_string() const {
    return fmt::format("({} {} {})", left_->to_string(), token_,
                       right_->to_string());
}

Evaluation::~Evaluation() {}
