/// Copyright (c) RenChu Wang - All Rights Reserved

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define SWAP(TY, A, B) \
    do {               \
        TY tmp = A;    \
        A = B;         \
        B = tmp;       \
    } while (0)

#define LEFT_CHILD(I) ((I) << 1) + 1
#define RIGHT_CHILD(I) ((I) << 1) + 2

// Comparator is used to abstract away the comparison function.
// If returns conceptually, s0 - s1.
// @param s0: The first int instance.
// @param s1: The second int instance.
// @return A positive integer if s0 > s1,
// negative integer if s0 < s1, 0 if s0 == s1.
typedef int (*comparator)(int s0, int s1);

// Sorter is used to abstract away the sorting method.
// It takes in an array, its size, and a Comparator.
// @param array: The array to sort.
// @param size: The length of the array.
// @param cmp: The comparator function.
// @return 0 if completed successfully. 1 otherwise.
typedef void (*sorter)(int* array, int size, comparator cmp);

// Merge sort.
void merge_sort(int* array, int size, comparator cmp);

// Heap sort.
void heap_sort(int* array, int size, comparator cmp);

// Insertion sort.
void insertion_sort(int* array, int size, comparator cmp);

static void merge(int* array, int half, int end, comparator cmp);
static void build_max_heap(int* array, int size, comparator cmp);
static void down_heap(int* array, int index, int size, comparator cmp);

void merge_sort(int* array, int size, comparator cmp) {
    // No need to sort if size is small enough.
    if (size <= 1) {
        return;
    }

    int half = size >> 1;

    // Sort first half.
    merge_sort(array, half, cmp);

    // Sort second half.
    merge_sort(array + half, size - half, cmp);

    // Merge both parts (in place).
    merge(array, half, size, cmp);
}

void heap_sort(int* array, int size, comparator cmp) {
    build_max_heap(array, size, cmp);

    // Sorting this array by always extracting the tip of the heap.
    for (int i = size - 1; i >= 0; --i) {
        // Swapping out the head to the end of heap
        // because it's the max in array[0:i]
        SWAP(int, array[0], array[i]);

        // i is the new effective heap size after each iteration.
        down_heap(array, 0, i, cmp);
    }
}

void insertion_sort(int* array, int size, comparator cmp) {
    // Pick the element first.
    for (int i = 1; i < size; ++i) {
        // Then insert it into the priority queue in order.
        for (int j = i; j >= 1 && cmp(array[j - 1], array[j]) > 0; --j) {
            SWAP(int, array[j - 1], array[j]);
        }
    }
}

void merge(int* array, int half, int end, comparator cmp) {
    // The index of the eventual sorted array.
    int index = 0;
    int* sorted_array = calloc(end, sizeof(int));

    // Picking the smaller instance of two arrays according to cmp.
    int idx1 = 0, idx2 = half;
    while (idx1 < half && idx2 < end) {
        if (cmp(array[idx1], array[idx2]) <= 0) {
            sorted_array[index++] = array[idx1++];
        } else {
            sorted_array[index++] = array[idx2++];
        }
    }

    // Unpack the rest into the sorted array.
    while (idx1 < half) {
        sorted_array[index++] = array[idx1++];
    }
    while (idx2 < end) {
        sorted_array[index++] = array[idx2++];
    }

    // Copy it back so as to "modify in place".
    assert(index == end);
    memcpy(array, sorted_array, end * sizeof(int));

    free(sorted_array);
}

void build_max_heap(int* array, int size, comparator cmp) {
    for (int i = (size >> 1) - 1; i >= 0; --i) {
        // Perform down heap on index i.
        down_heap(array, i, size, cmp);
    }
}

void down_heap(int* array, int idx, int size, comparator cmp) {
    // Index of left child.
    int left_idx = LEFT_CHILD(idx);

    // Index of right child.
    int right_idx = RIGHT_CHILD(idx);

    // Index of the bigger child.
    int bigger_idx;

    if (left_idx >= size) {
        // No child.
        return;
    } else if (left_idx == size - 1) {
        // Only child is the left child.
        bigger_idx = left_idx;
    } else {
        // Find the bigger child.
        if (cmp(array[left_idx], array[right_idx]) > 0) {
            bigger_idx = left_idx;
        } else {
            bigger_idx = right_idx;
        }
    }

    if (cmp(array[idx], array[bigger_idx]) < 0) {
        // Ensure heap property.
        SWAP(int, array[idx], array[bigger_idx]);

        // Recursive call to maintain heap property.
        down_heap(array, bigger_idx, size, cmp);
    }
}

int main() {}
