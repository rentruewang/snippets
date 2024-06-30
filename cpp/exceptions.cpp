// Copyright (c) 2024 RenChu Wang - All Rights Reserved

#include <iostream>
#include <string>

/// https://stackoverflow.com/questions/315948/c-catching-all-exceptions
int main() {
    try {
        throw std::string("anything would be caught");
    } catch (const std::string& str) {
        std::cout << "Caught string: " << str << '\n';
    } catch (...) {
        std::cout << "Default pattern\n";
    }
    std::cout << "done\n";

    return 0;
}
