#include <iostream>

using namespace std;

namespace A {

void functionInA();

namespace B {

void functionInB();

}

}  // namespace A

// namespace "A" has no tag member named "ClassA"
// class A::ClassA {};

using namespace A;
// The compiler doesn't know if this is a definition of a new function
// or an implementation of the declaration in namespace.
// void functionInA() {
//     cout << "A function\n";
// }

void A::functionInA() {
    cout << "A function\n";
}

using namespace A::B;

void functionInB() {
    cout << "B function\n";
}

int main() {
    A::functionInA();
    A::B::functionInB();

    return 0;
}
