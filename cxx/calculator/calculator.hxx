// Copyright (c) 2024 RenChu Wang - All Rights Reserved

#pragma once

#include <functional>
#include <memory>
#include <string>

using namespace std;

/// API: Lit, Var create two pointer to expressions.
/// that has simplify(), to_string(), Add, Sub, Mul as methods.

class Expression : public enable_shared_from_this<Expression> {
   public:
    shared_ptr<Expression> Add(const shared_ptr<Expression>& other) const;
    shared_ptr<Expression> Sub(const shared_ptr<Expression>& other) const;
    shared_ptr<Expression> Mul(const shared_ptr<Expression>& other) const;

    virtual shared_ptr<const Expression> simplify() const = 0;
    virtual string to_string() const = 0;

    virtual ~Expression();
};

class Literal : public Expression {
   public:
    Literal(int data);

    string to_string() const override;
    shared_ptr<const Expression> simplify() const override;

    int data() const;

    ~Literal() override;

   private:
    int data_;
};

class Variable : public Expression {
   public:
    Variable(string data);

    string to_string() const override;
    shared_ptr<const Expression> simplify() const override;

    ~Variable() override;

   private:
    string data_;
};

class Evaluation : public Expression {
   public:
    Evaluation(shared_ptr<const Expression> left,
               shared_ptr<const Expression> right,
               string token,
               function<int(int, int)> func);
    ~Evaluation() override;

    string to_string() const override;
    shared_ptr<const Expression> simplify() const override;

   private:
    shared_ptr<const Expression> left_;
    shared_ptr<const Expression> right_;
    string token_;
    function<int(int, int)> func_;
};
