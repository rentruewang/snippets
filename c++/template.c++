#include <iostream>
using namespace std;

template <typename T>
T larger(T a, T b) {
    T result = (a > b) ? a : b;
    return result;
}

template <typename T>
bool operator<<(T a, T b) {
    return a < b;
}

template <typename T>
class Container {
   public:
    Container(T value) noexcept { value_ = value; }

    T operator()() const { return value_; }

    bool operator<(const Container& other) const {
        cout << "   --- Container cmp called. ---   ";
        return value_ < other.value_;
    }

   private:
    T value_;
};

int main() {
    int i = 5, j = 6, k;
    long l = 10, m = 5, n;
    k = larger<int>(i, j);
    n = larger<long>(l, m);
    cout << k << endl;
    cout << n << endl;

    cout << "1 << 2: " << (Container<int>(1) << Container<int>(2)) << endl;
    cout << "1 << 0: " << (Container<int>(1) << Container<int>(0)) << endl;
    return 0;
}
