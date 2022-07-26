package main

import "fmt"

type EmptyInterface interface{}

type SomethingInterface interface {
	Something() int
}

var _ SomethingInterface = A{}

type A struct {
	Number int
}

func (a A) Something() int {
	return a.Number
}

type B struct{}

func main() {
	var a = A{1}

	sa := SomethingInterface(a)
	fmt.Printf("%v, %T, %v, %T\n", a, a, sa, sa)

	var b = B{}

	// cannot convert b (variable of type B) to type SomethingInterface:
	// B does not implement SomethingInterface (missing Something method)
	// sb := SomethingInterface(b)

	sb := EmptyInterface(b)
	fmt.Printf("%v, %T, %v, %T\n", b, b, sb, sb)
}
