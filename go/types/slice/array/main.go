package main

import "fmt"

// The conversions in this file from slices to arrays requires go 20+.
func main() {
	var slice []int
	var array [3]int

	slice = []int{1, 2, 3, 4, 5}
	array = [3]int(slice)

	fmt.Println(slice, array)

	// Haha this is not the syntax. Remember there is a shorter one...
	// cannot convert array (variable of type [3]int) to type []int
	// slice = []int(array)
	slice = array[:]
	fmt.Println(slice, array)

	slice = []int{1, 2}
	// panic: runtime error: cannot convert slice with length 2 to array or pointer to array with length 3
	array = [3]int(slice)

	fmt.Println(slice, array)
}
