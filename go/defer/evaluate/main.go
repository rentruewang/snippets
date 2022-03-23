package main

import (
	"errors"
	"fmt"
)

// https://stackoverflow.com/questions/42703707/when-defer-func-evaluates-its-parameters

func main() {
	a()
}

func a() {
	var err error
	defer func() {
		if err != nil {
			fmt.Printf("1st defer: %s\n", err)
		} else {
			fmt.Println("1st defer: defer not error")
		}
	}()
	defer func(err error) {
		if err != nil {
			fmt.Printf("2nd defer: %s\n", err)
		} else {
			fmt.Println("2nd defer: defer not error")
		}
	}(err)

	err = errors.New("new error")
	if err != nil {
		return
	}
}
