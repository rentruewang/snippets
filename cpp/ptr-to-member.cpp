/// Copyright (c) RenChu Wang - All Rights Reserved

#include <iostream>

using namespace std;

class WithMember {
   public:
    int a;
    void f(int b) {
        cout << "The value of b is " << b << endl;
        cout << "Address of this is " << *this << endl;
    }

    friend ostream& operator<<(ostream& os, const WithMember& x) {
        os << "{a: " << x.a << "}";
        return os;
    }
};

int main() {
    // declare pointer to data member
    int WithMember::*ptiptr = &WithMember::a;

    // declare a pointer to member function
    void (WithMember::*ptfptr)(int) = &WithMember::f;

    // create an object of class type X
    WithMember some_object;

    // initialize data member
    some_object.*ptiptr = 10;

    cout << "The value of a is " << some_object.*ptiptr << endl;

    // call member function
    (some_object.*ptfptr)(20);
}
