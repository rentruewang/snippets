/// Copyright (c) RenChu Wang - All Rights Reserved

#include <iostream>

using namespace std;

class Member {
   public:
    int a;
    void f(int b) {
        cout << "The value of b is " << b << endl;
        cout << "Address of this is " << *this << endl;
    }

    friend ostream& operator<<(ostream& os, const Member& x) {
        os << "{a: " << x.a << "}";
        return os;
    }
};

int main() {
    // declare pointer to data member
    int Member::*ptiptr = &Member::a;

    // declare a pointer to member function
    void (Member::*ptfptr)(int) = &Member::f;

    // create an object of class type X
    Member some_object;

    // initialize data member
    some_object.*ptiptr = 10;

    cout << "The value of a is " << some_object.*ptiptr << endl;

    // call member function
    (some_object.*ptfptr)(20);
}
