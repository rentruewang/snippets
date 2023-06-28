package main

import (
	"fmt"
	"math/rand"
)

func main() {
	a := make(chan string)
	b := make(chan string)

	go func() { a <- "a" }()
	go func() { b <- "b" }()

	if rand.Intn(2) == 0 {
		a = nil
		fmt.Println("nil a")
	} else {
		b = nil
		fmt.Println("nil b")
	}

	// If a channel is set to nil, it's "disabled" in a select statement.
	select {
	case s := <-a:
		fmt.Println("got", s)
	case s := <-b:
		fmt.Println("got", s)
	}
}
