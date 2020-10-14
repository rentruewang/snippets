package main

import "fmt"

type Fooer interface {
	Add()
	Dummy()
}

type Foo struct {
	Field int
}
// Please refer to https://stackoverflow.com/a/44372954
func (f *Foo) Dummy() {}
func (f *Foo) Add()   { f.Field += 1 }

func main() {
	var f1 Foo
	var f2 *Foo = &Foo{Field: 3}

	// ! Error happens here. Refer to the stackoverflow link above
	// DoFoo(f1)
	DoFoo(f2)

	fmt.Println("---")

	// DoFoo(f1)
	DoFoo(f2)
}

func DoFoo(f Fooer) {
	f.Add()
	fmt.Printf("[%T] %+v\n", f, f)
}
