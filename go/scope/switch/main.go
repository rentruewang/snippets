package main

import (
	"fmt"
	"strings"
)

func main() {
	cmds := []string{"pop", "inc 1 3", "push 2"}
	for _, cmd := range cmds {
		ops := strings.Split(cmd, " ")
		switch ops[0] {
		case "pop":
			if len(ops) != 1 {
				panic("ValueError")
			}

			// So I can define variables in a go switch
			i := 1
			fmt.Println(i)
		case "push":
			if len(ops) != 2 {
				panic("ValueError")
			}

			// Also I could define anonymous functions
			func() {
				fmt.Println("hello")
			}()
		case "inc":
			if len(ops) != 3 {
				panic("ValueError")
			}
		}
	}
}
