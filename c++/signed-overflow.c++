#include <iostream>

// This file, when compiled with g++, causes the loop to never end.
// g++ assumes that signed overflow will never happen
// and translate the code into the following:
//
// int main() {
//     for (int i = 0; i < 9 * 0x20000001; i += 0x20000001) {
//         std::cout << i << std::endl;
//     }
// }
//
// clang++ is fine though.
//
int main() {
    for (int i = 0; i < 9; ++i) {
        std::cout << i * 0x20000001 << std::endl;
    }
}
