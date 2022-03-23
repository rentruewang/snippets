package main

import "fmt"

// https://golang.org/ref/spec#Method_declarations
// https://stackoverflow.com/a/65441367

type DoSomething interface {
	Do(a, b int) int
}

func CallDS(dsth DoSomething, a, b int) int {
	out := dsth.Do(a, b)
	fmt.Println(out)
	return out
}

// invalid receiver type DoSomething (pointer or interface type)
// func (dsth DoSomething) Recv(a, b int) int {
// 	return dsth.Do(a, b)
// }

// https://stackoverflow.com/a/44412899
type IntP *int

// invalid receiver type IntP (pointer or interface type)
// func (ip IntP) Hi() int {
// 	return int(*ip)
// }

func Conv(ip IntP) int {
	return int(*ip)
}

type A struct{}

func (a A) Do(i, j int) int {
	return i + j
}

func main() {
	var d DoSomething = A{}
	fmt.Println(d.Do(5, 6))

	a := 789
	var ip IntP = &a
	fmt.Println(ip, *ip, (*int)(ip), (int)(*ip))
}
