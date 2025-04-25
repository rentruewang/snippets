/// Copyright (c) RenChu Wang - All Rights Reserved

#include <iostream>

using namespace std;

namespace a {

void function_in_a();

class ClassInA {
   public:
    void method();
};

namespace b {

void function_in_b();

class ClassInB {
   public:
    void method();
};

}  // namespace b

}  // namespace a

namespace a {
void function_in_a() {
    cout << "A function\n";
}
}  // namespace a

using namespace a;

void ClassInA::method() {
    cout << "A.method\n";
}

void b::function_in_b() {
    cout << "B function\n";
}

using namespace a::b;

void ClassInB::method() {
    cout << "B.method\n";
}

int main() {
    a::function_in_a();
    a::b::function_in_b();

    a::ClassInA().method();
    a::b::ClassInB().method();

    using namespace a::b;
    function_in_b();

    return 0;
}
