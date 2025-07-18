/// Copyright (c) RenChu Wang - All Rights Reserved

#include "calculator.hpp"

#include <string>

using namespace std;

shared_ptr<expression> expression::operator+(
    const shared_ptr<expression>& other) const {
    return make_shared<evaluation>(shared_from_this(), other, "+",
                                   [](int a, int b) { return a + b; });
}

shared_ptr<expression> expression::operator-(
    const shared_ptr<expression>& other) const {
    return make_shared<evaluation>(shared_from_this(), other, "-",
                                   [](int a, int b) { return a - b; });
}

shared_ptr<expression> expression::operator*(
    const shared_ptr<expression>& other) const {
    return make_shared<evaluation>(shared_from_this(), other, "*",
                                   [](int a, int b) { return a * b; });
}

shared_ptr<expression> expression::operator/(
    const shared_ptr<expression>& other) const {
    return make_shared<evaluation>(shared_from_this(), other, "/",
                                   [](int a, int b) { return a / b; });
}

expression::~expression() {}

literal::literal(int data) : data_(data) {}

shared_ptr<const expression> literal::simplify() const {
    return shared_from_this();
}

literal::operator string() const {
    return to_string(data_);
}

int literal::data() const {
    return data_;
}

literal::~literal() {}

variable::variable(string data) : data_(data) {}

shared_ptr<const expression> variable::simplify() const {
    return shared_from_this();
}

variable::operator string() const {
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

evaluation::operator string() const {
    return string(*left_) + " " + token_ + " " + string(*right_);
}

evaluation::~evaluation() {}
