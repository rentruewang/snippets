package main

import (
	"fmt"
	"math/rand"
	"time"
)

func boring(message string) {
	for i := 0; i < 10; i++ {
		fmt.Println(message, i)
		time.Sleep(time.Duration(rand.Intn(5e2)) * time.Millisecond)
	}
}

func main() {
	boring("Boring!")

	go boring("Interesting!")

	fmt.Println("I'm listening")
	time.Sleep(1 * time.Second)
	fmt.Println("You're boring. I'm leaving.")
}
