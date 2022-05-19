package main

import "fmt"

// type someStruct struct {
// 	field int
// }

// method must have no type parameters
// func (ss someStruct) GenericFunc[T any] () {}

type something[T any] struct {
	field T
}

func (s something[T]) A(param T) {
	fmt.Println("A", s.field, param)
}

// cannot use generic type someOtherStruct[T any] without instantiation
// func (s someOtherStruct) B() {}

// method must have no type parameters
// func (s someOtherStruct[T]) C[E] (param E) {}

func (s something[E]) D(param E) {
	fmt.Println("D", s.field, param)
}

func main() {
	something[int]{1}.A(2)
	something[int]{3}.D(4)

	// something[string]{3}.D(4)
}
