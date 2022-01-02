package main

import "fmt"

type Fooer interface {
	Add()
	Dummy()
	// syntax error: unexpected {, expecting semicolon or newline or }.
	// Partial() { Add(); Dummy() }
}

type Fooerer interface {
	Fooer
}

type Foo struct {
	Field int
}

type Anything interface{}

// Please refer to https://stackoverflow.com/a/44372954
func (f *Foo) Dummy() {}
func (f *Foo) Add()   { f.Field += 1 }

func willFail(fr *Fooer) {}

func retinterf() interface{} {
	return 8
}

func DoFoo(f Fooerer) {
	f.Add()
	fmt.Printf("[%T] %+v\n", f, f)

	var i int = retinterf().(int)
	fmt.Println(i)

	// The following line panics
	// var d float32 = retinterf().(float32)
	// fmt.Println(d)
}

func takeInterface(something interface{}) {
}

type fa = func(i interface{})
type fb = func(o Anything)

func main() {
	var f1 Foo
	var f2 *Foo = &Foo{Field: 3}

	// willFail(&f1)

	// I'm just using f1 as demonstration
	_ = f1

	// Anything is not interface{}, but it has no constraint so it could be an interface.
	var any Anything = f2
	fmt.Println(any.(*Foo))
	takeInterface(any)

	var first fa = func(i interface{}) {
		i.(*Foo).Dummy()
	}
	var second fb = func(i Anything) {
		i.(*Foo).Dummy()
	}
	fmt.Printf("%T %T\n", first, second)

	// But Anything is not interface{} !
	// cannot use second (type func(Anything)) as type func(interface {}) in assignment
	// first = second

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
