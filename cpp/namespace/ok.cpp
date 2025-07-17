/// Copyright (c) RenChu Wang - All Rights Reserved

#include <iostream>

using namespace std;

namespace a {

void function_in_a();

class class_in_a {
   public:
    void method();
};

namespace b {

void function_in_b();

class class_in_b {
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

void class_in_a::method() {
    cout << "A.method\n";
}

void b::function_in_b() {
    cout << "B function\n";
}

using namespace a::b;

void class_in_b::method() {
    cout << "B.method\n";
}

int main() {
    a::function_in_a();
    a::b::function_in_b();

    a::class_in_a().method();
    a::b::class_in_b().method();

    using namespace a::b;
    function_in_b();

    return 0;
}
