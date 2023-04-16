#include <iostream>

class ConstMember {
   public:
    ConstMember(int x) : member_(x) {}

   private:
    const int member_;
};

class NormalMember {
   public:
    NormalMember(int x) : member_(x) {}

   private:
    int member_;
};

int main() {
    // No problem doing this.
    NormalMember nm{3};
    nm = NormalMember{4};

    ConstMember cm{9};
    // ConstMember& ConstMember::operator=(ConstMember&&)’ is implicitly deleted
    // because the default definition would be ill-formed
    //
    // operator= is deleted because of const member.
    //
    //  cm = ConstMember{100};
}
