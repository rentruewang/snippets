package main

import "fmt"

func checkAndAssign[T any](value T, err error) T {
	if err != nil {
		panic(err)
	}

	return value
}

func maybeRaise() (int, error) {
	return 3, nil
}

func acceptInt(value int, err error) {
	fmt.Println("This actually works!", value, err)
}

func acceptFour(int, error, int, error) {

}

func main() {
	val := checkAndAssign(maybeRaise())
	fmt.Println(val)

	acceptInt(maybeRaise())

	// 2-valued maybeRaise() (value of type (int, error)) where single value is expected
	// acceptFour(maybeRaise(), maybeRaise())
}
