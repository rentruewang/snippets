package redefine

import "fmt"

func Function() {}

// A function cannot be defined twice in the same file.
// func Function() {}

// However, init can. See Effective Go: https://golang.org/doc/effective_go#init
func init() {
	fmt.Println("Execute the first init")
}
