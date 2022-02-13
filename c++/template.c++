#include <iostream>
using namespace std;

template <typename T>
T larger(T a, T b) {
    T result;
    result = (a > b) ? a : b;
    return (result);
}

int main() {
    int i = 5, j = 6, k;
    long l = 10, m = 5, n;
    k = larger<int>(i, j);
    n = larger<long>(l, m);
    cout << k << endl;
    cout << n << endl;
    return 0;
}
