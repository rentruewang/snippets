// Copyright (c) 2024 RenChu Wang - All Rights Reserved

#include <iostream>

using namespace std;

class member {
   public:
    int a;
    void f(int b) {
        cout << "The value of b is " << b << endl;
        cout << "Address of this is " << *this << endl;
    }

    friend ostream& operator<<(ostream& os, const member& x) {
        os << "{a: " << x.a << "}";
        return os;
    }
};

int main() {
    // declare pointer to data member
    int member::*ptiptr = &member::a;

    // declare a pointer to member function
    void (member::*ptfptr)(int) = &member::f;

    // create an object of class type X
    member some_object;

    // initialize data member
    some_object.*ptiptr = 10;

    cout << "The value of a is " << some_object.*ptiptr << endl;

    // call member function
    (some_object.*ptfptr)(20);
}
