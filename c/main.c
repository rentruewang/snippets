#include <stdio.h>
#include <stdlib.h>

void cfunction(const void* p) {}
void function(void* p) {}

int main(int argc, char const* argv[]) {
    const int* array = calloc(100, sizeof(int));

    // Warning on this line
    function(array);

    // This line is ok.
    cfunction(array);

    free((void*)array);

    return 0;
}
