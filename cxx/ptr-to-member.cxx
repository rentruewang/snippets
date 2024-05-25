// Copyright (c) 2024 RenChu Wang - All Rights Reserved

#include <iostream>

using namespace std;

class X {
   public:
    int a;
    void f(int b) {
        cout << "The value of b is " << b << endl;
        cout << "Address of this is " << *this << endl;
    }

    friend ostream& operator<<(ostream& os, const X& x) {
        os << "{a: " << x.a << "}";
        return os;
    }
};

int main() {
    // declare pointer to data member
    int X::*ptiptr = &X::a;

    // declare a pointer to member function
    void (X::*ptfptr)(int) = &X::f;

    // create an object of class type X
    X xobject;

    // initialize data member
    xobject.*ptiptr = 10;

    cout << "The value of a is " << xobject.*ptiptr << endl;

    // call member function
    (xobject.*ptfptr)(20);
}
