#include <functional>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <string_view>

using namespace std;

// Using shared_ptr<int> x would have been safe here
// function<int(void)> f(shared_ptr<int> x) {}
function<int(void)> f(shared_ptr<int>& x) {
    return [&]() { return *x; };
}

int main() {
    // Code from here
    // https://alexgaynor.net/2019/apr/21/modern-c++-wont-save-us/

    string s = "hello ";

    // initial value of reference to non-const must be an lvalue
    //
    // non-const lvalue reference to type 'basic_string<...>' cannot bind to a
    // temporary of type 'basic_string<...>'
    // string& r = s + "world";

    // object backing the pointer will be destroyed at the end of the
    // full-expression [-Wdangling-gsl]
    // string_view sv = s + "world";
    // cout << s << sv << "\n";

    // This should be UB.
    function<int(void)> y{nullptr};
    {
        auto x{make_shared<int>(4)};
        y = f(x);
    }
    cout << y() << endl;

    // This is uninitialized.
    optional<int> x(nullopt);
    cout << *x << "\n";
}
