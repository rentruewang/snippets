package main

import (
	"fmt"
	"math/rand"
	"time"
)

const repeat = 5

func boring(message string) {
	for i := 0; i < repeat; i++ {
		fmt.Println(message, i)
		time.Sleep(time.Duration(rand.Intn(5e2)) * time.Millisecond)
	}
}

func boringChan(message string, ch chan<- string) {
	for i := 0; i < repeat; i++ {
		ch <- fmt.Sprintf("%s, %d", message, i)
		time.Sleep(time.Duration(rand.Intn(5e2)) * time.Millisecond)
	}
}

// The generator pattern, then channel acts as a handle to the service.
func boringGenerator(message string) <-chan string {
	ch := make(chan string)

	go func() {
		for i := 0; i < repeat; i++ {
			ch <- fmt.Sprintf("%s, %d", message, i)
			time.Sleep(time.Duration(rand.Intn(5e2)) * time.Millisecond)
		}
		close(ch)
	}()

	return ch
}

// The multiplexing pattern.
func fanIn(inputA, inputB <-chan string) <-chan string {
	ch := make(chan string)

	go func() {
		for msg := range inputA {
			ch <- msg
		}
	}()

	go func() {
		for msg := range inputB {
			ch <- msg
		}
	}()

	return ch
}

func fanInSelect(inputA, inputB <-chan string) <-chan string {
	ch := make(chan string)

	go func() {
		timeout := time.After(1 * time.Second)

		for {
			select {
			case ch <- <-inputA:
			case ch <- <-inputB:
			case <-timeout:
				ch <- "Timeout. Leaving"
				return
			}
		}
	}()

	return ch
}

func safeQuitter(message string) (<-chan string, chan string) {
	ch := make(chan string)
	quit := make(chan string)

	go func() {
		for {
			select {
			case ch <- message:
			case <-quit:
				fmt.Println("cleanup() should be performed here")
				quit <- "done quitting"
				return
			}
		}
	}()

	return ch, quit
}

func daisyChain(left, right chan int) {
	left <- 1 + <-right
}

func main() {
	boring("Boring!")

	ch := make(chan string)
	go boringChan("Boring channel!", ch)
	for i := 0; i < repeat; i++ {
		fmt.Println(<-ch)
	}

	chg := boringGenerator("Boring generator!")
	for msg := range chg {
		fmt.Println(msg)
	}

	chf := fanIn(boringGenerator("A"), boringGenerator("B"))
	for i := 0; i < repeat; i++ {
		fmt.Println(<-chf)
	}

	chfs := fanInSelect(boringGenerator("C"), boringGenerator("D"))
	for i := 0; i < repeat; i++ {
		fmt.Println(<-chfs)
	}

	chq, quit := safeQuitter("hihi")
	for i := 0; i < repeat; i++ {
		fmt.Println(<-chq)
	}
	quit <- "Quit now"
	fmt.Println(<-quit)

	const n = 10000
	leftmost := make(chan int)
	right := leftmost
	left := leftmost
	for i := 0; i < n; i++ {
		right = make(chan int)
		go daisyChain(left, right)
		left = right
	}
	go func() { right <- 1 }()
	fmt.Println("leftmost:", <-leftmost)
}
