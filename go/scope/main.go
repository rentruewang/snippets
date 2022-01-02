package main

import (
	"fmt"

	"github.com/rentruewang/tmp/scope/subdir"
)

func main() {
	sth := subdir.Something{}

	// implicit assignment of unexported field 'privateField' in subdir.Something literal
	// sth = subdir.Something{-1}

	// cannot refer to unexported field 'privateField' in struct literal of type subdir.Something
	// sth = subdir.Something{privateField: 8}

	fmt.Println(sth.PrivateField())
}
