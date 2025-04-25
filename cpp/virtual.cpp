/// Copyright (c) RenChu Wang - All Rights Reserved

#include <iostream>
#include <memory>

using namespace std;

class Base {
   public:
    Base() { cout << "In Base1()\n"; }

    virtual ~Base() { cout << "In ~Base1()\n"; }
};

class Der1 : public Base {
   public:
    Der1() : Base() { cout << "In Derived1()\n"; }

    ~Der1() override { cout << "In ~Derived1()\n"; }
};

class Der2 {
   public:
    Der2() { cout << "In Base2()\n"; }

    // This is undefined behavior.
    ~Der2() { cout << "In ~Base2()\n"; }
};

class Der3 : public Der2 {
   public:
    Der3() : Der2() { cout << "In Derived2()\n"; }

    ~Der3() { cout << "In ~Derived2()\n"; }
};

int main() {
    { unique_ptr<Base> ptr1 = make_unique<Der1>(); }
    cout << "\n";
    { unique_ptr<Der2> ptr2 = make_unique<Der3>(); }
    cout << "\n";
}
