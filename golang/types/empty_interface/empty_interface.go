package main

import "fmt"

// note that any is not of type interface{}, but a new type
type any interface{}

// used for type checks
func callAnyFunc(f func(interface{})) {
	f(0)
}

func takesAny(a any) {
	fmt.Println(a)
}

func main() {
	// any is not actually interface so this line fails
	// callAnyFunc(takesAny)

	// This line fails with a similar reason
	// var f func(interface{}) = takesAny
	// fmt.Println(f)
}
