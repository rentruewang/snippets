/// Copyright (c) RenChu Wang - All Rights Reserved

#include <iostream>
#include <memory>

using namespace std;

class base_1 {
   public:
    base_1() { cout << "In base_1()\n"; }

    virtual ~base_1() { cout << "In ~base_1()\n"; }
};

class der_1 : public base_1 {
   public:
    der_1() : base_1() { cout << "In der_1()\n"; }

    ~der_1() override { cout << "In ~der_1()\n"; }
};

class base_2 {
   public:
    base_2() { cout << "In base_2()\n"; }

    // This is undefined behavior.
    ~base_2() { cout << "In ~base_2()\n"; }
};

class der_2 : public base_2 {
   public:
    der_2() : base_2() { cout << "In der_2()\n"; }

    ~der_2() { cout << "In ~der_2()\n"; }
};

int main() {
    {
        unique_ptr<base_1> ptr1 = make_unique<der_1>();
    }
    cout << "\n";
    {
        unique_ptr<base_2> ptr2 = make_unique<der_2>();
    }
    cout << "\n";
}
