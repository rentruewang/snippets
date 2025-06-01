/// Copyright (c) RenChu Wang - All Rights Reserved

#include <iostream>

using namespace std;

class ViewInit {
   public:
    ViewInit(int data) : data_(data) {
        cout << "ViewConstructors(" << data << ") called\n";
    }

    ViewInit(const ViewInit& other) : data_(other.data_) {
        cout << "ViewConstructors(const&" << data_ << ") called\n";
    }

    ViewInit(ViewInit&& other) : data_(other.data_) {
        cout << "ViewConstructors(&&" << data_ << ") called\n";
    }

    int data() const { return data_; }

    friend ostream& operator<<(ostream& os, const ViewInit& vc) {
        os << vc.data_;
        return os;
    }

    ~ViewInit() { cout << "~ViewConstructors(" << data_ << ") called\n"; }

   private:
    int data_;
};

ViewInit f(int i) {
    return ViewInit(i);
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
