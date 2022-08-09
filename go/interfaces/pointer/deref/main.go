package main

import "fmt"

type Integer struct {
	Value int
}

func (i *Integer) Inc() {
	i.Value++
}

func (i *Integer) Print() {
	fmt.Println(i)
}

func main() {
	// Dereference does not copy, but assignment does.
	// https://stackoverflow.com/questions/38443348/does-dereferencing-a-struct-return-a-new-copy-of-struct

	fmt.Println("integer value")
	var integerValue Integer = Integer{0}
	integerValue.Inc()
	integerValue.Print()
	fmt.Println()

	fmt.Println("integer copied")
	integerCopied := integerValue
	integerCopied.Inc()
	integerCopied.Print()
	integerValue.Print()
	fmt.Println()

	fmt.Println("integer pointer")
	var integerPointer *Integer = &Integer{0}
	integerPointer.Inc()
	integerPointer.Print()
	fmt.Println()

	// It's like C++.
	// Dereference does not copy.
	fmt.Println("dereference call method")
	(*integerPointer).Inc()
	integerPointer.Print()
	fmt.Println()

	fmt.Println("shallow copy pointer")
	var anotherPointer *Integer = integerPointer
	anotherPointer.Inc()
	anotherPointer.Print()
	integerPointer.Print()
	fmt.Println()

	// Also like C++.
	// This makes a copy because a variable is created.
	fmt.Println("copy pointer to value")
	var integerPointerCopied Integer = *integerPointer
	integerPointerCopied.Inc()
	integerPointerCopied.Print()
	integerPointer.Print()
}
