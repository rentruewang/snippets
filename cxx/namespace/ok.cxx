#include <iostream>

using namespace std;

namespace A {

void functionInA();

class ClassInA {
   public:
    void method();
};

namespace B {

void functionInB();

class ClassInB {
   public:
    void method();
};

}  // namespace B

}  // namespace A

namespace A {
void functionInA() {
    cout << "A function\n";
}
}  // namespace A

using namespace A;

void ClassInA::method() {
    cout << "A.method\n";
}

void B::functionInB() {
    cout << "B function\n";
}

using namespace A::B;

void ClassInB::method() {
    cout << "B.method\n";
}

int main() {
    A::functionInA();
    A::B::functionInB();

    A::ClassInA().method();
    A::B::ClassInB().method();

    using namespace A::B;
    functionInB();

    return 0;
}
