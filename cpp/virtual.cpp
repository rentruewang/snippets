// Copyright (c) 2024 RenChu Wang - All Rights Reserved

#include <iostream>
#include <memory>

using namespace std;

class base_1 {
   public:
    base_1() { cout << "In Base1()\n"; }

    virtual ~base_1() { cout << "In ~Base1()\n"; }
};

class derived_1 : public base_1 {
   public:
    derived_1() : base_1() { cout << "In Derived1()\n"; }

    ~derived_1() override { cout << "In ~Derived1()\n"; }
};

class derived_2 {
   public:
    derived_2() { cout << "In Base2()\n"; }

    // This is undefined behavior.
    ~derived_2() { cout << "In ~Base2()\n"; }
};

class derived_3 : public derived_2 {
   public:
    derived_3() : derived_2() { cout << "In Derived2()\n"; }

    ~derived_3() { cout << "In ~Derived2()\n"; }
};

int main() {
    { unique_ptr<base_1> ptr1 = make_unique<derived_1>(); }
    cout << "\n";
    { unique_ptr<derived_2> ptr2 = make_unique<derived_3>(); }
    cout << "\n";
}
