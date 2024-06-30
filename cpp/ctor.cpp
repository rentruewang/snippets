// Copyright (c) 2024 RenChu Wang - All Rights Reserved

#include <iostream>
#include <string>

using namespace std;

#define NOT_USED [[maybe_unused]]

class only_copy {
   public:
    only_copy(string member) : member_(member) { cout << "init only copy\n"; }
    only_copy(const only_copy& other) : member_(other.member_) {
        cout << "copy only copy\n";
    }
    only_copy(only_copy&& other) = delete;
    const string& member() const { return member_; }

   private:
    string member_;
};

class only_move {
   public:
    only_move(string member) : member_(member) { cout << "init only move\n"; }
    only_move(const only_move& other) = delete;
    only_move(only_move&& other) : member_(std::move(other.member_)) {
        cout << "move only move\n";
    }
    const string& member() const { return member_; }

   private:
    string member_;
};

class have_both {
   public:
    have_both(string member) : member_(member) { cout << "init both\n"; }
    have_both(const have_both& other) : member_(other.member_) {
        cout << "copy both\n";
    }
    have_both(have_both&& other) : member_(std::move(other.member_)) {
        cout << "move both\n";
    }
    const string& member() const { return member_; }

   private:
    string member_;
};

template <typename T>
class does_not_use {
   public:
    void call_copy(NOT_USED const T& obj) {}
    void call_move(NOT_USED T&& obj) {}
};

template <typename T>
class use_copy {
   public:
    void call_copy(const T& obj) { T copied(obj); }
    void call_move(NOT_USED T&& obj) {}
};

template <typename T>
class use_move {
   public:
    void call_copy(NOT_USED const T& obj) {}
    void call_move(T&& obj) { T moved(std::move(obj)); }
};

template <typename T>
class use_both {
   public:
    void call_copy(const T& obj) { T copied(obj); }
    void call_move(T&& obj) { T moved(std::move(obj)); }
};

template <typename T>
class move_is_copy {
   public:
    void call_copy(NOT_USED const T& obj) {}
    void call_move(T&& obj) { T moved(obj); }
};

template <typename T>
class copy_is_move {
   public:
    void call_copy(const T& obj) { T copied(std::move(obj)); }
    void call_move(NOT_USED T&& obj) {}
};

int main() {
    only_copy has_copy{"copy"};
    only_move has_move{"move"};
    have_both has_both{"both"};

    NOT_USED does_not_use<only_copy> dnu_copy;
    NOT_USED does_not_use<only_move> dnu_move;
    NOT_USED does_not_use<have_both> dnu_both;

    NOT_USED use_copy<only_copy> uc_copy;
    NOT_USED use_copy<only_move> uc_move;
    NOT_USED use_copy<have_both> uc_both;

    NOT_USED use_move<only_copy> um_copy;
    NOT_USED use_move<only_move> um_move;
    NOT_USED use_move<have_both> um_both;

    cout << "Use copy\n";

    use_copy<only_copy> uc_used_copy;
    NOT_USED use_copy<only_move> uc_used_move;
    use_copy<have_both> uc_used_both;

    uc_used_copy.call_copy(has_copy);

    // error: call to deleted constructor of 'OnlyMove'
    // uc_used_move.call_copy(has_move);

    uc_used_both.call_copy(has_both);

    cout << "\n";

    cout << "Use move\n";

    NOT_USED use_move<only_copy> um_used_copy;
    use_move<only_move> um_used_move;
    use_move<have_both> um_used_both;

    // error: rvalue reference to type 'OnlyCopy' cannot bind to lvalue of type
    // 'OnlyCopy'
    // um_used_copy.call_move(has_copy);

    // error: call to deleted constructor of 'OnlyCopy'
    // um_used_copy.call_move(move(has_copy));

    um_used_move.call_move(std::move(has_move));
    um_used_both.call_move(std::move(has_both));

    cout << "\n";

    cout << "Move is copy\n";

    move_is_copy<only_copy> mic_used_copy;
    NOT_USED move_is_copy<only_move> mic_used_move;
    move_is_copy<have_both> mic_used_both;

    mic_used_copy.call_move(std::move(has_copy));

    // error: rvalue reference to type 'OnlyCopy' cannot bind to lvalue of type
    // 'OnlyCopy'
    // mic_used_copy.call_move(has_copy);

    // error: call to deleted constructor of 'OnlyMove'
    // mic_used_move.call_move(move(has_move));

    // error: rvalue reference to type 'OnlyMove' cannot bind to lvalue of type
    // 'OnlyMove'
    // mic_used_move.call_move(has_move);

    mic_used_both.call_move(std::move(has_both));

    cout << "\n";

    cout << "Copy is move (but is copy)\n";
    // https://stackoverflow.com/questions/28595117/why-can-we-use-stdmove-on-a-const-object
    // https://stackoverflow.com/questions/27810535/why-does-calling-stdmove-on-a-const-object-call-the-copy-constructor-when-pass
    // https://stackoverflow.com/questions/63466914/move-semantics-vs-const-reference
    // https://stackoverflow.com/questions/4938875/do-rvalue-references-to-const-have-any-use

    copy_is_move<only_copy> cim_used_copy;
    NOT_USED copy_is_move<only_move> cim_used_move;
    copy_is_move<have_both> cim_used_both;

    cim_used_copy.call_copy(has_copy);
    cim_used_copy.call_copy(std::move(has_copy));

    // error: call to deleted constructor of 'OnlyMove'
    // cim_used_move.call_copy(std::move(has_move));

    // error: call to deleted constructor of 'OnlyMove'
    // cim_used_move.call_copy(has_move);

    cim_used_both.call_copy(std::move(has_both));

    use_both<only_copy> ub_copy;
    use_both<only_move> ub_move;
    use_both<have_both> ub_both;

    ub_copy.call_copy(has_copy);

    // error: call to deleted constructor of 'OnlyCopy'
    // ub_copy.call_move(has_move);

    // error: no viable conversion from 'typename std::remove_reference<OnlyMove
    // &>::type' (aka 'OnlyMove') to 'OnlyCopy'
    // ub_copy.call_move(move(has_move));

    // error: call to deleted constructor of 'OnlyMove'
    // ub_move.call_copy(has_move);
    ub_move.call_move(std::move(has_move));

    ub_both.call_copy(has_both);
    ub_both.call_move(std::move(has_both));

    return 0;
}
