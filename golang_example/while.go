package main

import "fmt"

func main() {
	// So Go permits empty space after ; in for loop
	for i := 0; i < 3; {
		i++
		fmt.Println(i)
	}
}
