package main

import "fmt"

func main() {
	array := [...]int{1, 2, 3}

	for _, v := range array {
		v = 8
		fmt.Println(v)
	}

	fmt.Println(array)

}
