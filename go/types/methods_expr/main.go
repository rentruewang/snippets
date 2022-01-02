package main

import (
	"fmt"
	"reflect"
)

type Foo int

func (f Foo) A() {
	fmt.Println("A")
}
func (f Foo) B() {
	fmt.Println("B")
}
func (f Foo) C() {
	fmt.Println("C")
}

func main() {
	var f Foo
	bara := func(m func(f Foo)) {
		m(f)
	}
	bara(Foo.A)

	barb := func(m func()) {
		m()
	}
	barb(f.B)

	barc := func(name string) {
		reflect.ValueOf(f).MethodByName(name).Call(nil)
	}
	barc("C")

}
