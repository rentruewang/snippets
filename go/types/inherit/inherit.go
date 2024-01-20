package main

import "fmt"

type BaseType struct {
	data int
}

func (bt BaseType) String() string {
	return fmt.Sprintf("BaseType{%d}", bt.data)
}

type InheritType struct {
	BaseType
}

func OnlyBase(bt BaseType) {
	fmt.Println(bt.String())
}

func main() {
	it := InheritType{}
	fmt.Println(it.String())

	// cannot use it (type InheritType) as type BaseType in argument to OnlyBase
	// as expected, Go does not have inheritance
	// OnlyBase(it)
}
