/// Copyright (c) RenChu Wang - All Rights Reserved

#pragma once

#include <functional>
#include <memory>
#include <string>

using namespace std;

/// API: Lit, Var create two pointer to expressions.
/// that has simplify(), to_string(), Add, Sub, Mul as methods.

class Expr : public enable_shared_from_this<Expr> {
   public:
    shared_ptr<Expr> operator+(const shared_ptr<Expr>& other) const;
    shared_ptr<Expr> operator-(const shared_ptr<Expr>& other) const;
    shared_ptr<Expr> operator*(const shared_ptr<Expr>& other) const;
    shared_ptr<Expr> operator/(const shared_ptr<Expr>& other) const;

    virtual shared_ptr<const Expr> simplify() const = 0;
    virtual string to_string() const = 0;

    virtual ~Expr();
};

class Lit : public Expr {
   public:
    Lit(int data);

    string to_string() const override;
    shared_ptr<const Expr> simplify() const override;

    int data() const;

    ~Lit() override;

   private:
    int data_;
};

class Var : public Expr {
   public:
    Var(string data);

    string to_string() const override;
    shared_ptr<const Expr> simplify() const override;

    ~Var() override;

   private:
    string data_;
};

class Eval : public Expr {
   public:
    Eval(shared_ptr<const Expr> left,
         shared_ptr<const Expr> right,
         string token,
         function<int(int, int)> func);
    ~Eval() override;

    string to_string() const override;
    shared_ptr<const Expr> simplify() const override;

   private:
    shared_ptr<const Expr> left_;
    shared_ptr<const Expr> right_;
    string token_;
    function<int(int, int)> func_;
};
