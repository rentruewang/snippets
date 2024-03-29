package main

import "fmt"

type Number interface {
	int64 | float64
}

type Custom interface {
	Method()
}

type SomeType struct {
	Field string
}

func (st SomeType) Method() {
	fmt.Println(st.Field)
}

func main() {
	// Initialize a map for the integer values
	ints := map[string]int64{
		"first":  34,
		"second": 12,
	}

	// Initialize a map for the float values
	floats := map[string]float64{
		"first":  35.98,
		"second": 26.99,
	}

	fmt.Printf("Non-Generic Sums: %v and %v\n",
		SumInts(ints),
		SumFloats(floats))

	fmt.Printf("Generic Sums: %v and %v\n",
		SumIntsOrFloats[string, int64](ints),
		SumIntsOrFloats[string, float64](floats))

	fmt.Printf("Generic Sums, type parameters inferred: %v and %v\n",
		SumIntsOrFloats(ints),
		SumIntsOrFloats(floats))

	fmt.Printf("Generic Sums with Constraint: %v and %v\n",
		SumNumbers(ints),
		SumNumbers(floats))

	fmt.Println()
	st := SomeType{"this is a string"}
	CheckCustomGenerics(st)
	CheckCustomInterface(st)

	fmt.Println()
	fmt.Println(Invoke(int64(3), AsFloat))

	// cannot use generic type ContainsSomething[T comparable] without instantiation
	// fmt.Println(ContainsSomething{Something: "hello"})

	fmt.Println()
	fmt.Println(ContainsSomething[string]{Something: "hello"})
	fmt.Println(ContainsSomething[int64]{Something: 789})
}

// SumInts adds together the values of m.
func SumInts(m map[string]int64) int64 {
	var s int64
	for _, v := range m {
		s += v
	}
	return s
}

// SumFloats adds together the values of m.
func SumFloats(m map[string]float64) float64 {
	var s float64
	for _, v := range m {
		s += v
	}
	return s
}

// SumIntsOrFloats sums the values of map m. It supports both floats and integers
// as map values.
func SumIntsOrFloats[K comparable, V int64 | float64](m map[K]V) V {
	var s V
	for _, v := range m {
		s += v
	}
	return s
}

// SumNumbers sums the values of map m. Its supports both integers
// and floats as map values.
func SumNumbers[K comparable, V Number](m map[K]V) V {
	var s V
	for _, v := range m {
		s += v
	}
	return s
}

// Just checking if custom interface can be used in generics
func CheckCustomGenerics[T Custom](t T) {
	fmt.Println("Using generics")
	t.Method()
}

func CheckCustomInterface(t Custom) {
	fmt.Println("Using interface")
	t.Method()
}

func Invoke[E Number, T Number](t T, f func(t T) E) E {
	fmt.Println("Invoke is called.")
	return f(t)
}

func AsFloat(i int64) float64 {
	return float64(i)
}

type ContainsSomething[T comparable] struct {
	Something T
}
