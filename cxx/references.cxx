// Copyright (c) 2024 RenChu Wang - All Rights Reserved

#include <iostream>

class ViewConstructors {
   public:
    ViewConstructors(int data) : data_(data) {
        std::cout << "ViewConstructors(" << data << ") called\n";
    }

    ViewConstructors(const ViewConstructors& other) : data_(other.data_) {
        std::cout << "ViewConstructors(const&" << data_ << ") called\n";
    }

    ViewConstructors(ViewConstructors&& other) : data_(other.data_) {
        std::cout << "ViewConstructors(&&" << data_ << ") called\n";
    }

    int data() const { return data_; }

    friend std::ostream& operator<<(std::ostream& os,
                                    const ViewConstructors& vc) {
        os << vc.data_;
        return os;
    }

    ~ViewConstructors() {
        std::cout << "~ViewConstructors(" << data_ << ") called\n";
    }

   private:
    int data_;
};

ViewConstructors f(int i) {
    return ViewConstructors(i);
}

int main() {
    // Lifetime extension, when bound to a const reference,
    // the lifetime of the temporary is extended to the end of the scope.
    // https://stackoverflow.com/q/11560339
    // https://stackoverflow.com/a/2822280
    // https://herbsutter.com/2008/01/01/gotw-88-a-candidate-for-the-most-important-const/
    const auto& r11 = f(11);
    std::cout << r11 << '\n';

    const auto r22 = f(22);
    std::cout << r22 << '\n';

    {
        const auto& r33 = f(33);
        std::cout << r33 << '\n';
    }

    {
        const auto r44 = f(44);
        std::cout << r44 << '\n';
    }

    std::cout << "done\n";

    return 0;
}
