package main

import "fmt"

// https://go.dev/doc/effective_go#conversions
// https://go.dev/doc/effective_go#interface_conversions
// https://go.dev/doc/effective_go#blank_implements

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
	// cannot convert sa (variable of type SomethingInterface) to A (need type assertion)
	// na := A(sa)
	na := sa.(A)
	fmt.Printf("%v, %T, %v, %T, %v, %T\n", a, a, sa, sa, na, na)

	var b = B{}

	// cannot convert b (variable of type B) to type SomethingInterface:
	// B does not implement SomethingInterface (missing Something method)
	// sb := SomethingInterface(b)
	sb := EmptyInterface(b)
	// cannot convert sb (variable of type EmptyInterface) to B (need type assertion)
	// nb := B(sb)
	nb := sb.(B)

	fmt.Printf("%v, %T, %v, %T, %v, %T\n", b, b, sb, sb, nb, nb)
}
