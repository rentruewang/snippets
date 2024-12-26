/// Copyright (c) RenChu Wang - All Rights Reserved

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE 11
#define DIGIT_WIDTH 16

#define MAX(A, B) (A) > (B) ? (A) : (B)

void counting_sort(int* array) {
    // Since array's domain is {1...}, 0 is used as a default value.
    int max = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        max = MAX(max, array[i]);
    }

    // counts[i] means there are count[i] * (i+1)
    int* counts = calloc(max, sizeof(int));
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        ++(counts[array[i] - 1]);
    }

    // Unpack the counts back to array.
    for (int i = 0, idx = 0; i < max; ++i) {
        for (int j = 0; j < counts[i]; ++j) {
            array[idx++] = i + 1;
        }
    }

    free(counts);
}

// It's the exact same operation as num & (1 << radix)
int radix_of(int num, int radix) {
    return (num >> radix) & 1;
}

// Sort by binary representation.
void radix_sort(int* array, int radix) {
    int cnt0 = 0, cnt1 = 0;

    // The array used to store temporary order.
    int* tmp = calloc(ARRAY_SIZE, sizeof(int));

    // Counting the total number of 0s and 1s at the given radix.
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (radix_of(array[i], radix)) {
            ++cnt1;
        } else {
            ++cnt0;
        }
    }

    // Assign the temporary array according to the radix.
    // This is equivalent with sorting stably along that radix.
    int idx0 = 0, idx1 = cnt0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (radix_of(array[i], radix)) {
            tmp[idx1++] = array[i];
        } else {
            tmp[idx0++] = array[i];
        }
    }

    assert(idx0 == cnt0);
    assert(idx1 == ARRAY_SIZE);

    // Free the temporary array.
    memcpy(array, tmp, sizeof(int) * ARRAY_SIZE);
    free(tmp);
}

int main() {
    {
        int array[ARRAY_SIZE] = {2, 4, 1, 2, 3, 2, 5, 3, 5, 1, 2};

        counting_sort(array);

        for (int i = 0; i < ARRAY_SIZE; ++i) {
            printf("%d ", array[i]);
        }
        printf("\n");
    }

    {
        int array[ARRAY_SIZE] = {2, 4, 1, 2, 3, 2, 5, 3, 5, 1, 2};

        for (int i = 0; i < DIGIT_WIDTH; ++i) {
            radix_sort(array, i);
        }

        for (int i = 0; i < ARRAY_SIZE; ++i) {
            printf("%d ", array[i]);
        }
        printf("\n");
    }

    return 0;
}
