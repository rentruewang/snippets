package main

import "fmt"

// any is a valid argument type!
func myPrintln(argument any) {
	fmt.Println(argument)
}

func main() {
	var v any = 3
	myPrintln(v)

	v = any(9)
	myPrintln(v)

	myPrintln(12)
}
