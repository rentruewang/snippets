package main

import (
	"fmt"
	"sort"
)

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

	s := []int{4, 2, 1, 3}
	v := s[:]
	sort.Slice(v, func(i, j int) bool {
		return v[i] < v[j]
	})
	fmt.Println(s, v)

	elem := &s[1]
	fmt.Println(s)
	*elem = 46
	fmt.Println(s)

	sl := make([]int, 100)
	fmt.Println(len(sl))

	sl = append(sl, 10)
	fmt.Println(len(sl))

	for i := 0; i < 100; i++ {
		sl[i] = i
	}
	fmt.Println(len(sl))
}
