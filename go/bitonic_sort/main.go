package main

import (
	"fmt"

	"golang.org/x/exp/constraints"
)

func ReverseInPlace[T any](array []T) {
	for idx := 0; idx < len(array)/2; idx++ {
		back := len(array) - idx - 1
		array[idx], array[back] = array[back], array[idx]

	}
}

func Concat[T any](first, second []T) []T {
	result := make([]T, len(first)+len(second))
	copy(result[:len(first)], first)
	copy(result[len(first):], second)
	return result
}

// BitonicSort is the bitonic sort algorithm. Runs in O(n log^2 n) time.
func BitonicSort[T constraints.Ordered](array []T) []T {
	switch len(array) {
	case 2:
		if array[0] > array[1] {
			return []T{array[1], array[0]}
		}
		fallthrough
	case 0:
		fallthrough
	case 1:
		return array
	}

	half := len(array) / 2

	// Not bitonic yet. Make the sequence bitonic.
	first := BitonicSort(array[:half])
	second := BitonicSort(array[half:])
	ReverseInPlace(second)

	bitonicSeq := Concat(first, second)

	return BitonicToSorted(bitonicSeq)
}

// BitonicToSorted converts a bitonic sequence into a sorted sequence.
// Runs in O(n log n) time.
func BitonicToSorted[T constraints.Ordered](seq []T) []T {
	if len(seq) <= 1 {
		return seq
	}

	smaller, larger := BitonicSplit(seq)

	smaller = BitonicToSorted(smaller)
	larger = BitonicToSorted(larger)

	return Concat(smaller, larger)
}

// BitonicSplit splits one bitonic sequence into 2 bitonic sequences,
// with any of the elements of the first one smaller than the second one.
func BitonicSplit[T constraints.Ordered](seq []T) (smaller, larger []T) {
	if len(seq) <= 1 {
		panic("unreachable")
	}

	seqLen := len(seq)
	last := seq[seqLen-1]

	// Since bitonic split only works on element with even elements,
	// append an element so that the biotnic split works properly.
	if seqLen%2 != 0 {
		seq = append(seq, last)
	}

	smaller, larger = bitonicSplitEven(seq)

	// Remove the added element, here seqLen must be the index of last element because of the append.
	if seqLen%2 != 0 {
		if smaller[len(smaller)-1] == last {
			smaller = smaller[:len(smaller)-1]
		} else {
			larger = larger[:len(larger)-1]
		}
	}

	return
}

// bitonicSplitEven uses bitonic split to split a sequence.
// This algorithm only handles sequences with even number of elements.
func bitonicSplitEven[T constraints.Ordered](seq []T) (smaller, larger []T) {
	if len(seq)%2 != 0 {
		panic("unreachable")
	}

	half := len(seq) / 2

	smaller = make([]T, half)
	larger = make([]T, half)

	for i := 0; i < half; i++ {
		// First assume first one is smaller, then swap if assumption is wrong.
		smaller[i] = seq[i]
		larger[i] = seq[i+half]

		if smaller[i] > larger[i] {
			smaller[i], larger[i] = larger[i], smaller[i]
		}
	}

	return
}

func main() {
	array := []int{5, 3, 4, 7, 10, 14, 13, 8, 2}
	array = BitonicSort(array)
	fmt.Println(array)
}
