//go:generate genny -in=$GOFILE -out=gen-$GOFILE gen "T=string,int"

package queue

import "github.com/cheekybits/genny/generic"

// NOTE: this is how easy it is to define a generic type
type T generic.Type

// TQueue is a queue of Ts.
type TQueue struct {
	items []T
}

func NewTQueue() *TQueue {
	return &TQueue{items: make([]T, 0)}
}
func (q *TQueue) Push(item T) {
	q.items = append(q.items, item)
}

func (q *TQueue) Pop() T {
	item := q.items[0]
	q.items = q.items[1:]
	return item
}
