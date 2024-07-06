#include <iostream>

using namespace std;

// This file, when compiled with g++, causes the loop to never end.
// g++ assumes that signed overflow will never happen
// and translate the code into the following:
//
// int main() {
//     for (int i = 0; i < 9 * 0x20000001; i += 0x20000001) {
//         cout << i << endl;
//     }
// }
//
// clang++ is fine though.
//
int main() {
    for (int i = 0; i < 9; ++i) {
        cout << i * 0x20000001 << endl;
    }
}
