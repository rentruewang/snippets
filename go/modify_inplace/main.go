package main

import "fmt"

func main() {
	slice := []int{1, 2, 3, 4, 5}

	for i, v := range slice {
		fmt.Printf("(%v,%v) ", i, v)
	}
	fmt.Println()

	// See, this would yield incorrect answer
	for i, v := range slice {
		if i == 2 || i == 3 {
			slice = append(slice[:i], slice[i+1:]...)
		}
		fmt.Printf("(%v,%v), %p, %v\n", i, v, &slice, slice)
	}

	fmt.Println(slice)
}
