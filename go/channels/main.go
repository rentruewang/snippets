package main

import "fmt"

func main() {
	a := make(chan int)
	b := make(chan int)

	go func() {
		// cannot use a (variable of type chan int) as int value in send
		// b <- a

		val := <-a
		b <- val
	}()

	go func() {
		a <- 123456
	}()

	fmt.Println(<-b)
}
