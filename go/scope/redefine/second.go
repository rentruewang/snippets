package redefine

import "fmt"

// A function cannot be defined if there is a function with
// the same name in the same package
// func Function() {}

// However, init is a special case.s
func init() {
	fmt.Println("Execute the second init")
}
