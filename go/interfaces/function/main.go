package main

import "fmt"

type DoSomething interface {
	Do(a, b int) int
}

func CallDS(dsth DoSomething, a, b int) int {
	out := dsth.Do(a, b)
	fmt.Println(out)
	return out
}

type DoFunc func(a, b int) int

// Implements DoSomething for DoFunc
func (dsthf DoFunc) Do(a, b int) int {
	return dsthf(a, b)
}

// Both function should implement `DoSomething`
func Add(a, b int) int { return a + b }
func Sub(a, b int) int { return a - b }

func main() {
	// Missing method
	// CallDS(Add, 1, 2)

	CallDS(DoFunc(Add), 1, 2)
	CallDS(DoFunc(Sub), 1, 2)
}
