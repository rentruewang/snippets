package main

import "fmt"

// See this
// https://tip.golang.org/ref/spec#Interface_types

type A interface {
	A(a int)
}

type B interface {
	B(b int)
}

type X interface {
	X(x int)
}

type C1 interface {
	// cannot use main.A in union (main.A contains methods)
	// cannot use main.B in union (main.B contains methods)
	// A | B

	~struct{ S string }
	// ~EqString

	// In a term of the form ~T, the underlying type of T must be itself, and T cannot be an interface.
	// ~SString

	X

	C(c int)
}

// C2 is a copy of C, except using an alias
type C2 interface {
	// cannot use main.A in union (main.A contains methods)
	// cannot use main.B in union (main.B contains methods)
	// A | B

	// ~struct{S string}
	~EqString

	// In a term of the form ~T, the underlying type of T must be itself, and T cannot be an interface.
	// ~SString

	X

	C(c int)
}

// CC1 is a copy of C, except no derived types are allowed
type CC1 interface {
	// cannot use main.A in union (main.A contains methods)
	// cannot use main.B in union (main.B contains methods)
	// A | B

	struct{ S string }
	// EqString

	// In a term of the form ~T, the underlying type of T must be itself, and T cannot be an interface.
	// ~SString

	X

	C(c int)
}

// CC2 is a copy of C, except no derived types are allowed
type CC2 interface {
	// cannot use main.A in union (main.A contains methods)
	// cannot use main.B in union (main.B contains methods)
	// A | B

	// struct{S string}
	EqString

	// In a term of the form ~T, the underlying type of T must be itself, and T cannot be an interface.
	// ~SString

	X

	C(c int)
}

type SString struct {
	S string
}

type EqString = struct {
	S string
}

type D EqString

func (d D) A(a int) {
	fmt.Println("D.A", d, a)
}

func (d D) B(b int) {
	fmt.Println("D.B", d, b)
}

func (d D) C(c int) {
	fmt.Println("D.C", d, c)
}

func (d D) X(x int) {
	fmt.Println("D.X", d, x)
}

// This will not work with CCC1 because you cannot add methods to another struct
type DD = EqString

// invalid receiver type struct{S string}
// func (dd DD) X(x int) {
// 	fmt.Println("DD.X", dd, x)
// }

// func (dd DD) C(c int) {
// 	fmt.Println("DD.C", dd, c)
// }

type E SString

func (e E) B(b int) {
	fmt.Println("E.B", e, b)
}

func (e E) C(c int) {
	fmt.Println("E.C", e, c)
}

func (e E) X(x int) {
	fmt.Println("E.X", e, x)
}

type F struct {
	S string
}

func (f F) C(c int) {
	fmt.Println("F.C", f, c)
}

func (f F) X(x int) {
	fmt.Println("F.X", f, x)
}

// interface contains type constraints
// func AcceptC(c C) {
// 	fmt.Println("Calling AcceptC")
// 	c.X(123)
// 	fmt.Println()
// }

func AcceptC1[T C1](c T) {
	fmt.Println("Calling AcceptC")
	fmt.Println("C.S", c.S)
	c.X(123)

	AcceptC2(c)
}

func AcceptC2[T C2](c T) {
	fmt.Println("Calling AcceptCC")
	fmt.Println("CC.S", c.S)
	c.X(123)
	fmt.Println()
}

func AcceptCC1[T CC1](c T) {
	fmt.Println("Calling AcceptCC1")
	fmt.Println("C.S", c.S)
	c.X(123)

	AcceptC2(c)
}

func AcceptCC2[T CC2](c T) {
	fmt.Println("Calling AcceptCC2")
	AcceptCC1(c)
}

func main() {
	d := D{S: "d"}
	e := E{S: "e"}
	f := F{S: "f"}

	AcceptC1(d)
	AcceptC1(e)
	AcceptC1(f)

	// struct{S string} does not implement CC1 (missing C method)
	// AcceptCC1(DD{S: "dd"})
}
