#include <iostream>
#include <memory>
#include <string>

using namespace std;

class SomeClass {
   public:
    SomeClass(string name) { _name = name; }
    ~SomeClass() {
        cout << "Destructor for SomeClass(" << _name << ") called.\n";
    }

   private:
    string _name;
};

int main() {
    auto ptr = make_unique<SomeClass>("first");

    cout << "Assign to another.\n";

    ptr = make_unique<SomeClass>("second");

    cout << "Finally done.\n";
}
