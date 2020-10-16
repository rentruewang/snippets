package main

import "fmt"

type Fooer interface {
	Add()
	Dummy()
}

type Fooerer interface {
	Fooer
}

type Foo struct {
	Field int
}

// Please refer to https://stackoverflow.com/a/44372954
func (f *Foo) Dummy() {}
func (f *Foo) Add()   { f.Field += 1 }

func willFail(fr *Fooer) {}

func main() {
	var f1 Foo
	var f2 *Foo = &Foo{Field: 3}

	// willFail(&f1)

	// I'm just using f1 as demonstration
	_ = f1

	// ! Error happens here. Refer to the stackoverflow link above
	// DoFoo(f1)
	DoFoo(f2)

	fmt.Println("---")

	// DoFoo(f1)
	DoFoo(f2)

	_, ok := interface{}(&Foo{}).(Fooerer)
	if ok {
		fmt.Println("ok")
	}
}

func DoFoo(f Fooerer) {
	f.Add()
	fmt.Printf("[%T] %+v\n", f, f)
}
