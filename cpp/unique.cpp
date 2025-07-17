/// Copyright (c) RenChu Wang - All Rights Reserved

#include <iostream>
#include <memory>

using namespace std;

template <typename T>
void print(T anything) {
    cout << anything << "\n";
}

template <typename T>
class some_class {
   public:
    some_class(T name) { name_ = name; }
    ~some_class() { print(name_); }

    T& name() { return name_; }
    const T& name() const { return name_; }

   private:
    T name_;
};

int main() {
    print("First experiment: 12345");
    {
        print(1);
        auto ptr = make_unique<some_class<int>>(3);
        print(2);
        ptr = make_unique<some_class<int>>(5);
        print(4);
    }

    print("Second experiment: 12345");
    {
        print(1);
        // 0 wouldn't appear in the output because it's an initialization.
        auto sc = some_class<int>(0);
        print(2);
        // Destructor called once here for the temporary object.
        sc = some_class<int>(3);
        sc.name() = 5;
        print(4);
    }
}
