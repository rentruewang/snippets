package main

import "fmt"

type Int int

func AcceptInt(i Int) Int {
	return i
}

func main() {
	i := 8

	// cannot use i (variable of type int) as Int value in argument to AcceptInt
	// o := AcceptInt(i)

	o := AcceptInt(Int(i))
	fmt.Println(o)
}
