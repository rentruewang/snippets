package main

import "fmt"

// https://stackoverflow.com/questions/33936081/golang-method-with-pointer-receiver
// https://stackoverflow.com/questions/45652560/interfaces-and-pointer-receivers

type myType int

type forVal interface {
	valMethod() int
}

type forPtr interface {
	ptrMethod() int
}

func (mt myType) valMethod() int {
	return int(mt)
}

func (mt *myType) ptrMethod() int {
	return int(*mt)
}

func acceptsValue(v forVal) {
	fmt.Printf("%t,%v\n", v, v.valMethod())
}

func acceptsPointer(v forPtr) {
	fmt.Printf("%t,%v\n", v, v.ptrMethod())
}

func main() {
	var intValue myType = 12
	acceptsValue(intValue)
	acceptsPointer(&intValue)

	var intPointer *myType = &intValue
	acceptsValue(*intPointer)
	acceptsPointer(intPointer)

	// I remember another example in this repo but I can't find it now.
	// You can't pass a value to an interface your pointer implements,
	// but you can pass a pointer to an interface your value implements.
	// The reason for that is that pointer methods may change state
	// But value methods don't.
	// That makes value methods thread safe and can be used on pointer methods.
	// It's all syntax sugar.

	// This line causes error!
	// acceptsPointer(intValue)
	acceptsValue(intPointer)
}
