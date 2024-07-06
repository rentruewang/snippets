#include <iostream>

using namespace std;

// Both g++ and clang++ produces the correct behavior
// and traps the overflow to inf.
int main() {
    double c = 1e99;

    // 1e+198
    cout << c * c << "\n";

    // 1e+297
    cout << c * c * c << "\n";

    // inf
    cout << c * c * c * c << "\n";
}
