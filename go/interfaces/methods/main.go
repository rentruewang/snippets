package main

import "fmt"

// type someStruct struct {
// 	field int
// }

// method must have no type parameters
// func (ss someStruct) GenericFunc[T any] () {}

type someOtherStruct[T any] struct {
	field T
}

func (sos someOtherStruct[T]) A(param T) {
	fmt.Println(sos.field, param)
}

// cannot use generic type someOtherStruct[T any] without instantiation
// func (sos someOtherStruct) B() {}

// method must have no type parameters
// func (sos someOtherStruct[T]) C[E] (param E) {}

func main() {}
