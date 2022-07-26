package main

import "fmt"

type Base struct {
	Something int
}

type EqBase = Base

// Completely equal to
// func (Base).DuplicateFunc()
func (eb EqBase) DuplicateFunc() {
	fmt.Println(eb.Something)
}

// method DuplicateFunc already declared for type Base struct{Something int}
// func (b Base) DuplicateFunc() {
// 	fmt.Println(b.Something)
// }

func main() {
	var base Base = Base{3}
	base.DuplicateFunc()

	base = EqBase{4}
	base.DuplicateFunc()
}
