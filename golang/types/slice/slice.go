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

	other:= slice[:]
	other[2] = 8
	fmt.Println(slice)
}
