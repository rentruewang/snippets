package main

import "fmt"

type Bar func()

var bar Bar

type Number interface {
	int | float64
}

type ReturnsInterface func(a int) interface{}

type ReturnsNumber[num Number] func(a int) num

type ReturnsInt func(a int) int

type WrapsInt struct {
	Int int
}

type ReturnsWrapsInt func(a int) WrapsInt

func main() {
	x := "hello world x"
	bar = func() {
		fmt.Println(x)
	}
	bar()

	var rif ReturnsInterface = func(b int) interface {} {
		return b
	}
	fmt.Println(rif(3))
	fmt.Printf("%T\n\n", rif)


	var ri ReturnsInt = func(b int) int {
		return b
	}
	fmt.Println(ri(18))
	fmt.Printf("%T\n\n", ri)

	// Not the same type
	// rif = ri

	// Duck typing here
	var rin ReturnsNumber[int] = func(b int) int {
		return b
	}
	fmt.Println(rin(88))
	fmt.Printf("%T\n\n", rin)

	// Does not work
	// rin = ri
}
