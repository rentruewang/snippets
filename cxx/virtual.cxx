#include <iostream>
#include <memory>

using namespace std;

class Base1 {
   public:
    Base1() { cout << "In Base1()\n"; }

    virtual ~Base1() { cout << "In ~Base1()\n"; }
};

class Derived1 : public Base1 {
   public:
    Derived1() : Base1() { cout << "In Derived1()\n"; }

    ~Derived1() override { cout << "In ~Derived1()\n"; }
};

class Base2 {
   public:
    Base2() { cout << "In Base2()\n"; }

    // This is undefined behavior.
    ~Base2() { cout << "In ~Base2()\n"; }
};

class Derived2 : public Base2 {
   public:
    Derived2() : Base2() { cout << "In Derived2()\n"; }

    ~Derived2() { cout << "In ~Derived2()\n"; }
};

int main() {
    { unique_ptr<Base1> ptr1 = make_unique<Derived1>(); }
    cout << "\n";
    { unique_ptr<Base2> ptr2 = make_unique<Derived2>(); }
    cout << "\n";
}
