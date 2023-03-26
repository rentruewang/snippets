package main

import "golang.org/x/exp/constraints"

func BitonicSort[T constraints.Ordered](array []T) []T {
	return make([]T, 0)
}

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

	smaller, larger = BitonicSplitEven(seq)

	// Remove the added element.
	if seqLen%2 != 0 {
		if smaller[len(smaller)-1] == last {
			smaller = smaller[:len(smaller)]
		} else {
			larger = larger[:len(larger)]
		}
	}

	return
}

func BitonicSplitEven[T constraints.Ordered](seq []T) (smaller, larger []T) {
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

func main() {}
