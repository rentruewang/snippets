package main

import (
	"fmt"
	"reflect"
)

func main() {
	typ := reflect.TypeOf(3)
	fmt.Println(typ)
	fmt.Println(typ.Kind() == reflect.Int)
	fmt.Println(typ.Kind() == reflect.Float32)
	fmt.Println(typ.Name())
}
