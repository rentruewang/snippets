package main

import (
	"fmt"

	"golang.org/x/exp/constraints"
)

func SortAndCount[T constraints.Ordered](arr []T) (int, []T) {
	n := len(arr)
	if n <= 1 {
		return 0, arr
	}

	cnt1, sorted1 := SortAndCount(arr[:n/2])
	cnt2, sorted2 := SortAndCount(arr[n/2:])
	inv, merged := MergeAndCount(sorted1, sorted2)

	return inv + cnt1 + cnt2, merged
}

func MergeAndCount[T constraints.Ordered](arr1, arr2 []T) (count int, merged []T) {
	for len(arr1) > 0 && len(arr2) > 0 {
		if arr1[0] <= arr2[0] {
			merged = append(merged, arr1[0])
			arr1 = arr1[1:]
		} else {
			count += len(arr1)
			merged = append(merged, arr2[0])
			arr2 = arr2[1:]
		}
	}

	merged = append(merged, arr1...)
	merged = append(merged, arr2...)

	return
}

func main() {
	arr := []int{9, 3, 2, 1, 4, 2}
	fmt.Println(SortAndCount(arr))
}
