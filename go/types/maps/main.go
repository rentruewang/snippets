package main

import "fmt"

type s2s map[string]string

type someStruct struct {
	field string
}

func main() {
	a := s2s{"1": "2"}
	fmt.Println(a)

	b := someStruct{"wer"}
	fmt.Println(b)

	// undeclared name: field compiler(UndeclaredName)
	// c := s2s{field: "wer"}

	// invalid field name "1" in struct literal compiler(InvalidLitField)
	// d := someStruct{"1": "3"}
}
