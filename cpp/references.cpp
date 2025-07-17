/// Copyright (c) RenChu Wang - All Rights Reserved

#include <iostream>

using namespace std;

class view_init {
   public:
    view_init(int data) : data_(data) {
        cout << "ViewConstructors(" << data << ") called\n";
    }

    view_init(const view_init& other) : data_(other.data_) {
        cout << "ViewConstructors(const&" << data_ << ") called\n";
    }

    view_init(view_init&& other) : data_(other.data_) {
        cout << "ViewConstructors(&&" << data_ << ") called\n";
    }

    int data() const { return data_; }

    friend ostream& operator<<(ostream& os, const view_init& vc) {
        os << vc.data_;
        return os;
    }

    ~view_init() { cout << "~ViewConstructors(" << data_ << ") called\n"; }

   private:
    int data_;
};

view_init f(int i) {
    return view_init(i);
}

int main() {
    // Lifetime extension, when bound to a const reference,
    // the lifetime of the temporary is extended to the end of the scope.
    // https://stackoverflow.com/q/11560339
    // https://stackoverflow.com/a/2822280
    // https://herbsutter.com/2008/01/01/gotw-88-a-candidate-for-the-most-important-const/
    const auto& r11 = f(11);
    cout << r11 << '\n';

    const auto r22 = f(22);
    cout << r22 << '\n';

    {
        const auto& r33 = f(33);
        cout << r33 << '\n';
    }

    {
        const auto r44 = f(44);
        cout << r44 << '\n';
    }

    cout << "done\n";

    return 0;
}
