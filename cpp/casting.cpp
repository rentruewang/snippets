/// Copyright (c) RenChu Wang - All Rights Reserved

#include <iostream>

class Printable {
   public:
    virtual void print() const = 0;
};

class CustomInt;
class CustomFloat;

class CustomInt : public Printable {
   public:
    CustomInt();
    CustomInt(int number);

    operator int() const;
    operator float() const;
    operator CustomFloat() const;

    void print() const override {
        std::cout << "CustomInt: " << value_ << std::endl;
    }

   private:
    int value_;
};

class CustomFloat : public Printable {
   public:
    CustomFloat();
    CustomFloat(float a);

    operator int() const;
    operator float() const;
    operator CustomInt() const;

    void print() const override {
        std::cout << "CustomFloat: " << value_ << std::endl;
    }

   private:
    float value_;
};

// Implementations

CustomInt::CustomInt() : value_(0) {}
CustomInt::CustomInt(int number) : value_(number) {}
CustomInt::operator int() const {
    return value_;
}
CustomInt::operator float() const {
    return static_cast<float>(value_);
}
CustomInt::operator CustomFloat() const {
    return CustomFloat(static_cast<float>(value_));
}

CustomFloat::CustomFloat() : value_(0.0f) {}
CustomFloat::CustomFloat(float a) : value_(a) {}
CustomFloat::operator int() const {
    return static_cast<int>(value_);
}
CustomFloat::operator float() const {
    return value_;
}
CustomFloat::operator CustomInt() const {
    return CustomInt(static_cast<int>(value_));
}

int main() {
    CustomInt custom_int(5);
    CustomFloat custom_float(3.14f);

    custom_int.print();
    custom_float.print();

    auto casted_float = static_cast<CustomFloat>(custom_int);
    casted_float.print();

    auto casted_int = static_cast<CustomInt>(custom_float);
    casted_int.print();

    return 0;
}
