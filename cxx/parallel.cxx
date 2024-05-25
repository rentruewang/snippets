// Copyright (c) 2024 RenChu Wang - All Rights Reserved

#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
void print_vector(std::vector<T> vec) {
    std::cout << "[ ";
    for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << "]\n";
}

int main() {
    std::vector<std::string> vec = {"a", "b", "c"};
    print_vector(vec);

    std::for_each(vec.begin(), vec.end(), [](auto& item) { item += "_mod"; });
    print_vector(vec);
}
