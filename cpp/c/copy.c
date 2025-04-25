/// Copyright (c) RenChu Wang - All Rights Reserved

#include <stdio.h>

typedef struct Array {
    int array[4];
} Array;

int main() {
    Array a = {.array = {1, 2, 3, 42}};
    for (int i = 0; i < 4; ++i) {
        printf("%d ", a.array[i]);
    }
    printf("\n");

    Array b = a;
    b.array[2] -= 100;
    for (int i = 0; i < 4; ++i) {
        printf("%d ", a.array[i]);
    }
    printf("\n");
    for (int i = 0; i < 4; ++i) {
        printf("%d ", b.array[i]);
    }
    printf("\n");

    b = a;
    for (int i = 0; i < 4; ++i) {
        printf("%d ", b.array[i]);
    }
    printf("\n");

    // https://stackoverflow.com/questions/32313150/array-type-char-is-not-assignable
    // array type 'int[3]' is not assignable
    //
    // int c[3] = {3, 242, 1}, d[3];
    // d = c;
    // for (int i = 0; i < 3; ++i) {
    //     printf("%d ", d[i]);
    // }
    // printf("\n");
}
