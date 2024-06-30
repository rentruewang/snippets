// Copyright (c) 2024 RenChu Wang - All Rights Reserved

#include <iostream>

using namespace std;

namespace a {

void function_in_a();

namespace b {

void function_in_b();

}

}  // namespace a

// namespace "a" has no tag member named "class_a"
// class a::class_a {};

using namespace a;
// The compiler doesn't know if this is a definition of a new function
// or an implementation of the declaration in namespace.
// void function_in_a() {
//     cout << "A function\n";
// }

void a::function_in_a() {
    cout << "A function\n";
}

using namespace a::b;

// undefined reference to `a::b::function_in_b()'
// void function_in_b() {
//     cout << "B function\n";
// }

void a::b::function_in_b() {
    cout << "B function\n";
}

int main() {
    a::function_in_a();

    a::b::function_in_b();

    return 0;
}
