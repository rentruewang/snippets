/// Copyright (c) RenChu Wang - All Rights Reserved

class ConstMem {
   public:
    ConstMem(int x) : member_(x) {}

   private:
    const int member_;
};

class NormMem {
   public:
    NormMem(int x) : member_(x) {}

   private:
    int member_;
};

int main() {
    // No problem doing this.
    NormMem nm{3};
    nm = NormMem{4};

    ConstMem cm{9};
    // const_member& const_member::operator=(const_member&&)’ is implicitly
    // deleted because the default definition would be ill-formed
    //
    // operator= is deleted because of const member.
    //
    //  cm = const_member{100};
}
