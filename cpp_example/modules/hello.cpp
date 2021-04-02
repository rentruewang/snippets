// It seems that module has to be placed here
module;

#include <iostream>

// However if this line is placed on the first line, there would be a compiler
// error. I think it works somewhat like #include and actually copies text in a
// smart way
export module hello;

export void hello() {
    std::cout << "hello";
}
