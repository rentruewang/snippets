package main

import (
	"encoding/json"
	"fmt"
	"log"
	"strings"
)

type Animal int

const (
	Unknown Animal = iota
	Gopher
	Zebra
)

func get() interface{} {
	return 3
}

type TupleUInt [2]uint

func (a *Animal) UnmarshalJSON(b []byte) error {
	var s string
	if err := json.Unmarshal(b, &s); err != nil {
		return err
	}
	switch strings.ToLower(s) {
	default:
		*a = Unknown
	case "gopher":
		*a = Gopher
	case "zebra":
		*a = Zebra
	}

	return nil
}

func multiReturn() (a, b int) {
	a = 3
	b = 4
	return
}

func (a Animal) MarshalJSON() ([]byte, error) {
	var s string
	switch a {
	default:
		s = "unknown"
	case Gopher:
		s = "gopher"
	case Zebra:
		s = "zebra"
	}

	return json.Marshal(s)
}

type TupleInt [2]int

func (ti *TupleInt) Inc() {
	ti[0]++
	ti[1]++
}

type Cat interface {
	Meow() string
}

type Lion struct {
}

type Tiger struct{ name string }

type Leopard struct {
	name   string
	number int
}

func (t Tiger) Meow() string { return "I'm a tiger" }

func (l Leopard) Meow() string { return "I'm a leopard" }

// func (l Lion) Meow() string {
// 	return "roar"
// }

func (l *Lion) Meow() string {
	return "roar ptr"
}

var Override string = "not overridden"

// func GetBigCat() Cat    { return Lion{} }
func GetBigCatPtr() Cat { return &Lion{} }

func main() {

	fmt.Println("Overridden", Override)
	Override = "overridden"
	fmt.Println("Overridden", Override)

	blob := `["gopher","armadillo","zebra","unknown","gopher","bee","gopher","zebra"]`
	var zoo []Animal
	if err := json.Unmarshal([]byte(blob), &zoo); err != nil {
		log.Fatal(err)
	}

	census := make(map[Animal]int)
	for _, animal := range zoo {
		census[animal]++
	}

	fmt.Printf("Zoo Census:\n* Gophers: %d\n* Zebras:  %d\n* Unknown: %d\n",
		census[Gopher], census[Zebra], census[Unknown])

	smap := make(map[string]string)
	json.Unmarshal([]byte(`{"a":"b", "c":"d"}`), &smap)
	fmt.Println(smap, smap["a"], smap["c"])

	i := 0
	for i = 0; i <= 100; i++ {
	}
	fmt.Println(i)

	tuint := interface{}([2]uint{3, 4})
	if v, ok := tuint.(TupleUInt); ok {
		fmt.Println("Implicit cast", v)
	} else {
		fmt.Println("No implicit cast", v)
	}

	var s string
	var ok bool
	if s, ok = get().(string); ok {
		fmt.Println("Ok", s)
	} else {
		fmt.Println("Not ok", s)
	}

	var x interface{} = 999
	y := x.(int)
	y++

	fmt.Println(x, y)

	ti := TupleInt{333, 444}
	ti.Inc()

	fmt.Println(ti)
	var iti interface{}
	iti = ti
	// ptr := &iti.(TupleInt)
	// the above line is equal to:
	newti := iti.(TupleInt)
	ptr := &newti
	// hence the operation is disallowed as it only adds confusion

	ptr.Inc()

	fmt.Println(ti)

	var l Cat
	// l := GetBigCat()
	l = GetBigCatPtr()
	// fmt.Println(l.Meow(), lptr.Meow())
	fmt.Println(l.Meow())

	// A list of fat pointers.
	li := make([]interface{}, 0)

	li = append(li, int32(1))
	li = append(li, float64(1.5))

	fmt.Println(li)

	catlist := make([]Cat, 0)
	catlist = append(catlist, Tiger{})
	catlist = append(catlist, Leopard{})

	fmt.Println(catlist)

	fmt.Println([3][2]int{})
	arr := [3][2]int{
		[2]int{1, 2},
		[2]int{3, 4},
		// will use default
		// [2]int{3, 4},
		[2]int{5},
	}
	fmt.Printf("%T, %v, %v, %v\n", arr, arr, arr[2], arr[2][1])
}
