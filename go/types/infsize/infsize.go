package main

import "fmt"

// InfSize has infinite size
// This does not compile, as expected
// illegal cycle in declaration of InfSize compiler InvalidDeclCycle
// type InfSize struct {
// 	// Not a pointer, so it doesn't have a fixed size.
// 	field InfSize
// }

type FiniteSize struct {
	// Pointer is ok.
	field *FiniteSize
}

func main() {
	fs := FiniteSize{nil}
	fmt.Println(fs)
}
