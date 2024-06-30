// Copyright (c) 2024 RenChu Wang - All Rights Reserved

#include <iostream>

class some_class {
   public:
    some_class(int i) : member(i) {}
    int& alias = member;
    const int& const_alias = member;
    int member;
};

int main() {
    auto sc = some_class{1};
    std::cout << sc.member << ' ' << sc.alias << ' ' << sc.const_alias << '\n';
    sc.member = 2;
    std::cout << sc.member << ' ' << sc.alias << ' ' << sc.const_alias << '\n';
    sc.alias = 3;
    std::cout << sc.member << ' ' << sc.alias << ' ' << sc.const_alias << '\n';

    // expression must be a modifiable lvalue
    // sc.const_alias = 4;
    // std::cout << sc.member << ' ' << sc.alias << ' ' << sc.const_alias <<
    // '\n';
}
