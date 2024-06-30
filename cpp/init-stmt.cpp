// Copyright (c) 2024 RenChu Wang - All Rights Reserved

#include <iostream>

int main() {
    using namespace std;

    if (int i = 3; i < 2) {
        cout << "hi " << i << "\n";
    } else {
        cout << "bye " << i << "\n";
    }

    switch (int i = 3; i) {
        case 1:
        case 2:
            cout << "no\n";
            break;
        case 3:
            cout << "yes\n";
            break;
        default:
            cout << "definitely not";
            break;
    }
}
