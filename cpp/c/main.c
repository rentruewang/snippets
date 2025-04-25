/// Copyright (c) RenChu Wang - All Rights Reserved

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void c_function(const void* p) {}
void function(void* p) {}

typedef struct Pointer {
    void* pointer;
} Pointer;

typedef struct CPointer {
    const void* pointer;
} CPointer;

int main(int argc, char const* argv[]) {
    int* array = calloc(100, sizeof(int));

    // Warning on this line
    function(array);

    // This is ok.
    c_function(array);

    // Warning on this line.
    Pointer ptr_arr = {.pointer = array};
    function(ptr_arr.pointer);
    c_function(ptr_arr.pointer);

    // This is ok.
    const Pointer const_ptr_arr = {.pointer = array};

    function(const_ptr_arr.pointer);
    c_function(const_ptr_arr.pointer);

    // This is an error
    // cparr.pointer = NULL;

    free((void*)array);

    void (*f_ptr)(void*);

    f_ptr = function;
    // f_ptr = c_function;

    if (0 < INFINITY) {
        printf("of course\n");
    }

    if (0 >= INFINITY) {
        printf("no\n");
    }

    return 0;
}
