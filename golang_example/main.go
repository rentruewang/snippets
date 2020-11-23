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

func main() {
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
}
