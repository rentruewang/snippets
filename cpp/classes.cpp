/// Copyright (c) RenChu Wang - All Rights Reserved

#include <iostream>

using namespace std;

class SomeClass {
   public:
    SomeClass(int i) : member(i) {}
    int& alias = member;
    const int& const_alias = member;
    int member;
};

int main() {
    auto sc = SomeClass{1};
    cout << sc.member << ' ' << sc.alias << ' ' << sc.const_alias << '\n';
    sc.member = 2;
    cout << sc.member << ' ' << sc.alias << ' ' << sc.const_alias << '\n';
    sc.alias = 3;
    cout << sc.member << ' ' << sc.alias << ' ' << sc.const_alias << '\n';

    // expression must be a modifiable lvalue
    // sc.const_alias = 4;
    // cout << sc.member << ' ' << sc.alias << ' ' << sc.const_alias <<
    // '\n';
}
