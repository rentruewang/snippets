package main

import "fmt"

func main() {
	channel := make(chan int, 1)

	channel <- 1

	select {
	case channel <- 2:
	default:
		fmt.Println("Not added")
	}

	fmt.Println(<-channel)

	channel <- 3
	fmt.Println(<-channel)
}
