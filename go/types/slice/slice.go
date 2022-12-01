package main

import "fmt"

func modifySlice0(slice []int) {
	if len(slice) == 0 {
		panic("The function fails")
	}
	slice[0] = -1
}

func main() {
	slice := []int{1, 2, 3, 4}
	fmt.Println(slice)

	modifySlice0(slice)
	fmt.Println(slice)

	other := slice[:]
	other[2] = 8
	fmt.Println(slice)

	empty := slice[4:]
	fmt.Println(empty)

	// panic: runtime error: slice bounds out of range [5:4]
	// willPanic := slice[5:]
	// fmt.Println(willPanic)
}
