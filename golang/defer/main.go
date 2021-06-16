package main

import "fmt"

func deferFunc() {
	fmt.Println("defer function called")
}

func returnFunc() int {
	fmt.Println("return function called")
	return 0
}

func Function() int {
	defer deferFunc()
	return returnFunc()
}

func main() {
	Function()
}
