package main

import "fmt"

type Bar func()

var bar Bar

func main() {
	x := "hello world x"
	bar = func() {
		fmt.Println(x)
	}
	bar()
}
