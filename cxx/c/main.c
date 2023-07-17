#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void cfunction(const void* p) {}
void function(void* p) {}

typedef struct Pointer {
    void* pointer
} Pointer;

typedef struct CPtr {
    const void* pointer
} CPtr;

int main(int argc, char const* argv[]) {
    const int* array = calloc(100, sizeof(int));

    // Warning on this line
    function(array);

    // This is ok.
    cfunction(array);

    // Warning on this line.
    Pointer parr = {.pointer = array};
    function(parr.pointer);
    cfunction(parr.pointer);

    // This is ok.
    const Pointer cparr = {.pointer = array};

    function(cparr.pointer);
    cfunction(cparr.pointer);

    // This is an error
    // cparr.pointer = NULL;

    free((void*)array);

    void (*fptr)(void*);

    fptr = function;
    fptr = cfunction;

    if (0 < INFINITY) {
        printf("of course\n");
    }

    if (0 >= INFINITY) {
        printf("no\n");
    }

    return 0;
}
