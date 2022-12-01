package main

import (
	"fmt"
	"sync"
	"time"
)

func main() {
	first := make(chan string)
	second := make(chan string)

	var wg sync.WaitGroup
	go func() {
		defer wg.Done()

		// This will not work because of this:
		// https://stackoverflow.com/a/67592125
		// It's the same as second <- <something>
		// The first time it runs, <-first is evaluated, but since
		// on the first try second <- <something> blocks,
		// the result is discarded, thus lost forever.
		//
		// for {
		// 	select {
		// 	case second <- <-first:
		// 		fmt.Println("Finally!")
		// 	default:
		// 		fmt.Println("Still waiting!")
		// 		time.Sleep(1 * time.Second)
		// 	}
		// }

		temp := ""
		inChan := first
		outChan := second

		for {
			if temp == "" {
				inChan = first
				outChan = nil
			} else {
				inChan = nil
				outChan = second
			}

			select {
			case outChan <- temp:
				fmt.Println("Send to second!")
			case temp = <-inChan:
				fmt.Println("Received from first!")
			default:
				fmt.Println("Still waiting!")
				time.Sleep(1 * time.Second)
			}
		}
	}()

	go func() {
		first <- "These are some special words."
	}()

	time.Sleep(3 * time.Second)

	fmt.Println("Output is:", <-second)

	wg.Wait()
}
