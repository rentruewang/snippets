// Copyright (c) 2024 RenChu Wang - All Rights Reserved

#pragma once

#include <functional>
#include <memory>
#include <string>

/// API: Lit, Var create two pointer to expressions.
/// that has simplify(), to_string(), Add, Sub, Mul as methods.

class expression : public std::enable_shared_from_this<expression> {
   public:
    std::shared_ptr<expression> operator+(
        const std::shared_ptr<expression>& other) const;
    std::shared_ptr<expression> operator-(
        const std::shared_ptr<expression>& other) const;
    std::shared_ptr<expression> operator*(
        const std::shared_ptr<expression>& other) const;

    virtual std::shared_ptr<const expression> simplify() const = 0;
    virtual std::string to_string() const = 0;

    virtual ~expression();
};

class literal : public expression {
   public:
    literal(int data);

    std::string to_string() const override;
    std::shared_ptr<const expression> simplify() const override;

    int data() const;

    ~literal() override;

   private:
    int data_;
};

class variable : public expression {
   public:
    variable(std::string data);

    std::string to_string() const override;
    std::shared_ptr<const expression> simplify() const override;

    ~variable() override;

   private:
    std::string data_;
};

class evaluation : public expression {
   public:
    evaluation(std::shared_ptr<const expression> left,
               std::shared_ptr<const expression> right,
               std::string token,
               std::function<int(int, int)> func);
    ~evaluation() override;

    std::string to_string() const override;
    std::shared_ptr<const expression> simplify() const override;

   private:
    std::shared_ptr<const expression> left_;
    std::shared_ptr<const expression> right_;
    std::string token_;
    std::function<int(int, int)> func_;
};
