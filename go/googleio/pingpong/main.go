package main

import (
	"fmt"
	"runtime/debug"
	"time"
)

type Ball struct{ Hits int }

func main() {
	table := make(chan *Ball)
	go player("ping", table)
	go player("pong", table)

	ball := Ball{Hits: 0}

	// Starts playing
	table <- &ball

	time.Sleep(1 * time.Second)

	// Steals the ball away
	// At this precise moment,
	// the main routine and one of the players are fighting for the ball,
	// One day, the main routine will win and take the ball.
	<-table

	// Show the full stack.
	debug.PrintStack()
	fmt.Println()

	// Doesn't seem to show all goroutines, contrary to the video.
	panic("Show me the stacks")
}

func player(name string, table chan *Ball) {
	// Because table has capacity 0,
	//
	// The two goroutines are blocked on these two lines:
	// ball := <- table
	// table <- ball
	//
	// until the two routines are synchronized.
	for {
		ball := <-table
		ball.Hits++
		fmt.Println(name, ball.Hits)
		time.Sleep(100 * time.Millisecond)
		table <- ball
	}
}
