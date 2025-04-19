/// Copyright (c) RenChu Wang - All Rights Reserved

#pragma once

#include <functional>
#include <memory>
#include <string>

using namespace std;

/// API: Lit, Var create two pointer to expressions.
/// that has simplify(), to_string(), Add, Sub, Mul as methods.

class expression : public enable_shared_from_this<expression> {
   public:
    shared_ptr<expression> operator+(const shared_ptr<expression>& other) const;
    shared_ptr<expression> operator-(const shared_ptr<expression>& other) const;
    shared_ptr<expression> operator*(const shared_ptr<expression>& other) const;
    shared_ptr<expression> operator/(const shared_ptr<expression>& other) const;

    virtual shared_ptr<const expression> simplify() const = 0;
    virtual string to_string() const = 0;

    virtual ~expression();
};

class literal : public expression {
   public:
    literal(int data);

    string to_string() const override;
    shared_ptr<const expression> simplify() const override;

    int data() const;

    ~literal() override;

   private:
    int data_;
};

class variable : public expression {
   public:
    variable(string data);

    string to_string() const override;
    shared_ptr<const expression> simplify() const override;

    ~variable() override;

   private:
    string data_;
};

class evaluation : public expression {
   public:
    evaluation(shared_ptr<const expression> left,
               shared_ptr<const expression> right,
               string token,
               function<int(int, int)> func);
    ~evaluation() override;

    string to_string() const override;
    shared_ptr<const expression> simplify() const override;

   private:
    shared_ptr<const expression> left_;
    shared_ptr<const expression> right_;
    string token_;
    function<int(int, int)> func_;
};
