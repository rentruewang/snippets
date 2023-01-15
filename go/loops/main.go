package main

import (
	"fmt"
	"sync"
)

func main() {
	var wg sync.WaitGroup

	// This might not print 0...9
	for i := 0; i < 10; i++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			// loop variable i captured by func literal loopclosure
			fmt.Println(i)
		}()
	}
	wg.Wait()
	fmt.Println()

	// This will because i is copied when passed in
	for i := 0; i < 10; i++ {
		wg.Add(1)
		go func(integer int) {
			defer wg.Done()
			fmt.Println(integer)
		}(i)
	}
	wg.Wait()
	fmt.Println()

	numbers := []int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
	for _, val := range numbers {
		wg.Add(1)
		go func() {
			defer wg.Done()
			// loop variable i captured by func literal loopclosure
			fmt.Println(val)
		}()
	}
	wg.Wait()
	fmt.Println()

	for _, val := range numbers {
		val := val
		wg.Add(1)
		go func() {
			defer wg.Done()
			fmt.Println(val)
		}()
	}
	wg.Wait()
	fmt.Println()
}
