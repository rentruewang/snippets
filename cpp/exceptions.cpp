// Copyright (c) 2024 RenChu Wang - All Rights Reserved

#include <iostream>
#include <string>

using namespace std;

/// https://stackoverflow.com/questions/315948/c-catching-all-exceptions
int main() {
    try {
        throw string("anything would be caught");
    } catch (const string& str) {
        cout << "Caught string: " << str << '\n';
    } catch (...) {
        cout << "Default pattern\n";
    }
    cout << "done\n";

    return 0;
}
