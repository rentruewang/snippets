package main

import (
	"fmt"

	"github.com/cheekybits/genny/parse/test/queue"
)

func main() {
	q := queue.NewIntQueue()
	q.Push(1)
	q.Push(2)

	x := q.Pop()

	fmt.Println(q, x)
}
