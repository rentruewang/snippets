/// Copyright (c) RenChu Wang - All Rights Reserved

#include "calculator.hpp"

#include <fmt/core.h>

using namespace std;

shared_ptr<Expr> Expr::operator+(
    const shared_ptr<Expr>& other) const {
    return make_shared<Eval>(shared_from_this(), other, "+",
                                   [](int a, int b) { return a + b; });
}

shared_ptr<Expr> Expr::operator-(
    const shared_ptr<Expr>& other) const {
    return make_shared<Eval>(shared_from_this(), other, "-",
                                   [](int a, int b) { return a - b; });
}

shared_ptr<Expr> Expr::operator*(
    const shared_ptr<Expr>& other) const {
    return make_shared<Eval>(shared_from_this(), other, "*",
                                   [](int a, int b) { return a * b; });
}

shared_ptr<Expr> Expr::operator/(
    const shared_ptr<Expr>& other) const {
    return make_shared<Eval>(shared_from_this(), other, "/",
                                   [](int a, int b) { return a / b; });
}

Expr::~Expr() {}

Lit::Lit(int data) : data_(data) {}

shared_ptr<const Expr> Lit::simplify() const {
    return shared_from_this();
}

string Lit::to_string() const {
    return fmt::format("{}", data_);
}

int Lit::data() const {
    return data_;
}

Lit::~Lit() {}

Var::Var(string data) : data_(data) {}

shared_ptr<const Expr> Var::simplify() const {
    return shared_from_this();
}

string Var::to_string() const {
    return data_;
}

Var::~Var() {}

Eval::Eval(shared_ptr<const Expr> left,
           shared_ptr<const Expr> right,
           string token,
           function<int(int, int)> func)
    : left_(left), right_(right), token_(token), func_(func) {}

shared_ptr<const Expr> Eval::simplify() const {
    auto lp = dynamic_pointer_cast<const Lit>(left_->simplify());
    auto rp = dynamic_pointer_cast<const Lit>(right_->simplify());

    // Do nothing because no simplification is needed.
    if (lp == nullptr || rp == nullptr) {
        return shared_from_this();
    }

    return make_shared<Lit>(func_(lp->data(), rp->data()));
}

string Eval::to_string() const {
    return fmt::format("({} {} {})", left_->to_string(), token_,
                       right_->to_string());
}

Eval::~Eval() {}
