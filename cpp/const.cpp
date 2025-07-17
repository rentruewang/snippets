/// Copyright (c) RenChu Wang - All Rights Reserved

class const_member {
   public:
    const_member(int x) : member_(x) {}

   private:
    const int member_;
};

class normal_member {
   public:
    normal_member(int x) : member_(x) {}
    int member() const { return member_; }

   private:
    int member_;
};

int main() {
    // No problem doing this.
    normal_member nm{3};
    nm = normal_member{4};

    const_member cm{9};
    // const_member& const_member::operator=(const_member&&)’ is implicitly
    // deleted because the default definition would be ill-formed
    //
    // operator= is deleted because of const member.
    //
    //  cm = const_member{100};
}
