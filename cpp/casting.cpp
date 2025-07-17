/// Copyright (c) RenChu Wang - All Rights Reserved

#include <iostream>

class printer {
   public:
    virtual void print() const = 0;
};

class custom_int;
class custom_float;

class custom_int : public printer {
   public:
    custom_int();
    custom_int(int number);

    operator int() const;
    operator float() const;
    operator custom_float() const;

    void print() const override {
        std::cout << "CustomInt: " << value_ << std::endl;
    }

   private:
    int value_;
};

class custom_float : public printer {
   public:
    custom_float();
    custom_float(float a);

    operator int() const;
    operator float() const;
    operator custom_int() const;

    void print() const override {
        std::cout << "CustomFloat: " << value_ << std::endl;
    }

   private:
    float value_;
};

// Implementations

custom_int::custom_int() : value_(0) {}
custom_int::custom_int(int number) : value_(number) {}
custom_int::operator int() const {
    return value_;
}
custom_int::operator float() const {
    return static_cast<float>(value_);
}
custom_int::operator custom_float() const {
    return custom_float(static_cast<float>(value_));
}

custom_float::custom_float() : value_(0.0f) {}
custom_float::custom_float(float a) : value_(a) {}
custom_float::operator int() const {
    return static_cast<int>(value_);
}
custom_float::operator float() const {
    return value_;
}
custom_float::operator custom_int() const {
    return custom_int(static_cast<int>(value_));
}

int main() {
    custom_int custom_int(5);
    custom_float custom_float(3.14f);

    custom_int.print();
    custom_float.print();

    auto casted_float = static_cast<class custom_float>(custom_int);
    casted_float.print();

    auto casted_int = static_cast<class custom_int>(custom_float);
    casted_int.print();

    return 0;
}
