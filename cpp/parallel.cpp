// Copyright (c) 2024 RenChu Wang - All Rights Reserved

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
void print_vector(vector<T> vec) {
    cout << "[ ";
    for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
        cout << *iter << " ";
    }
    cout << "]\n";
}

int main() {
    vector<string> vec = {"a", "b", "c"};
    print_vector(vec);

    for_each(vec.begin(), vec.end(), [](auto& item) { item += "_mod"; });
    print_vector(vec);
}
