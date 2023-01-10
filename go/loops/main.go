package main

import (
	"fmt"
	"sync"
)

func main() {
	var wg sync.WaitGroup

	// This might not print 0...9
	// for i := 0; i < 10; i++ {
	// 	go func() {
	// 		// 	// loop variable i captured by func literal loopclosure
	// 		fmt.Println(i)
	// 	}()
	// }

	// This will because i is copied when passed in
	for i := 0; i < 10; i++ {
		wg.Add(1)
		go func(integer int) {
			defer wg.Done()
			fmt.Println(integer)
		}(i)
	}

	wg.Wait()
}
