// Copyright (c) 2024 RenChu Wang - All Rights Reserved

#include "calculator.hxx"

#include <fmt/core.h>

using namespace std;

shared_ptr<expression> expression::operator+(
    const shared_ptr<expression>& other) const {
    return make_unique<evaluation>(shared_from_this(), other, "+",
                                   [](int a, int b) { return a + b; });
}

shared_ptr<expression> expression::operator-(
    const shared_ptr<expression>& other) const {
    return make_unique<evaluation>(shared_from_this(), other, "-",
                                   [](int a, int b) { return a - b; });
}

shared_ptr<expression> expression::operator*(
    const shared_ptr<expression>& other) const {
    return make_unique<evaluation>(shared_from_this(), other, "*",
                                   [](int a, int b) { return a * b; });
}

expression::~expression() {}

literal::literal(int data) : data_(data) {}

shared_ptr<const expression> literal::simplify() const {
    return shared_from_this();
}

string literal::to_string() const {
    return fmt::format("{}", data_);
}

int literal::data() const {
    return data_;
}

literal::~literal() {}

variable::variable(string data) : data_(data) {}

shared_ptr<const expression> variable::simplify() const {
    return shared_from_this();
}

string variable::to_string() const {
    return data_;
}

variable::~variable() {}

evaluation::evaluation(shared_ptr<const expression> left,
                       shared_ptr<const expression> right,
                       string token,
                       function<int(int, int)> func)
    : left_(left), right_(right), token_(token), func_(func) {}

shared_ptr<const expression> evaluation::simplify() const {
    auto lp = dynamic_pointer_cast<const literal>(left_->simplify());
    auto rp = dynamic_pointer_cast<const literal>(right_->simplify());

    // Do nothing because no simplification is needed.
    if (lp == nullptr || rp == nullptr) {
        return shared_from_this();
    }

    return make_shared<literal>(func_(lp->data(), rp->data()));
}

string evaluation::to_string() const {
    return fmt::format("({} {} {})", left_->to_string(), token_,
                       right_->to_string());
}

evaluation::~evaluation() {}
