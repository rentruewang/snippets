package main

import "fmt"

type S struct {
	val int
}

func (s *S) Modify() {
	s.val++
}

func main() {
	a := make([]S, 3)
	for i := 0; i < len(a); i++ {
		a[i] = S{val: i}
	}
	fmt.Println(a)
	b := a[1:]
	c := a[2:]
	for i := 0; i < len(b); i++ {
		b[i].Modify()
	}
	for i := 0; i < len(c); i++ {
		c[i].Modify()
	}
	fmt.Println(a)
}
