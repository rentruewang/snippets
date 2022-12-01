package main

import "fmt"

func TakeInt(i int) {
	fmt.Println(i)
}

type NewString string

func TakeString(s string) {
	fmt.Println(s)
}

func TakeNewString(ns NewString) {
	fmt.Println(ns)
}

func main() {
	// cannot convert 3.2 (untyped float constant) to int
	// integer := int(3.2)

	// cannot use 3.2 (untyped float constant) as int value in argument to TakeInt (truncated)
	// TakeInt(3.2)

	var integer int = 3.0
	TakeInt(integer)

	// cannot use integer (variable of type int) as float64 value in argument to TakeFloat
	// TakeFloat(integer)
	TakeInt(4.0)
	TakeInt(int(5.0))

	str := "This is a string"
	TakeString(str)
	// cannot use str (variable of type string) as NewString value in argument to TakeNewString
	// TakeNewString(str)
	TakeNewString(NewString(str))

	nstr := NewString(str)
	// cannot use nstr (variable of type NewString) as string value in argument to TakeString
	// TakeString(nstr)
	TakeString(string(nstr))
}
