package main

import "fmt"

func main() {
	// This is to safely insert an entry due to how append works internally.
	// https://github.com/charmbracelet/bubbles/issues/65
	slice := []string{"a", "b", "c"}
	index := 1

	before := slice[:index]

	// Copy the tail into a new slice so that it contains a separate underlying array.
	after := make([]string, len(slice[index:]))
	copy(after, slice[index:])

	// Now you can safely append an element to the head and concatenate the two slices.
	before = append(before, "NEW")
	slice = append(before, after...)
	fmt.Printf("%#v\n", slice)
}
