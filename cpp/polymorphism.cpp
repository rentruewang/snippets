/// Copyright (c) RenChu Wang - All Rights Reserved

#include <functional>
#include <iostream>
#include <string>
#include <vector>

struct A {
    int a;
};

struct B {
    float b;
};

struct C {
    std::string c;
};

int main() {
    A a{899};
    B b{935};
    C c{"song"};

    // Now I'm using closure to simulate a thunk,
    // which is a fat (function) pointer + data / state,
    // which can be used to implement dynamic dispatch (as in Go).
    std::function<int(int)> fa{[=](int num) { return a.a + num; }};

    std::function<int(int)> fb{[=](int num) { return b.b * num; }};

    std::function<int(int)> fc{[&](int num) { return int(c.c.size()) - num; }};

    std::vector<std::function<int(int)>> funcs{fa, fb, fc};

    // Dynamic dispatching.
    // This is very functional because this is similar to haskell's currying.
    // Each f is essentially a thunk in STG.
    for (auto&& f : funcs) {
        std::cout << f(1) << "\n";
    }
}
