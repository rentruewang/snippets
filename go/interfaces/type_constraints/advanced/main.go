package main

import "fmt"

// See this
// https://tip.golang.org/ref/spec#Interface_types

type Class1 interface {
	Method1(a int)
}

type Class2 interface {
	Method2(b int)
}

type Class3 interface {
	Method3(x int)
}

type DerivableStruct interface {
	// cannot use main.Class1 in union (main.Class1 contains methods)
	// cannot use main.Class2 in union (main.Class2 contains methods)
	// Class1 | Class2

	// ~ Allows for derivations. e.g. type X struct { S string }
	~struct{ S string }
	// ~EqString

	// In a term of the form ~T, the underlying type of T must be itself, and T cannot be an interface.
	// ~SString

	Class3

	InterfaceMethod(c int)
}

// DerivableString is a copy of C, except using an alias
type DerivableString interface {
	// cannot use main.Class1 in union (main.Class1 contains methods)
	// cannot use main.Class2 in union (main.Class2 contains methods)
	// Class1 | Class2

	// ~struct{S string}
	~EqString

	// In a term of the form ~T, the underlying type of T must be itself, and T cannot be an interface.
	// ~SString

	Class3

	InterfaceMethod(c int)
}

// NonDerivableStruct is a copy of C, except no derived types are allowed
type NonDerivableStruct interface {
	// cannot use main.Class1 in union (main.Class1 contains methods)
	// cannot use main.Class2 in union (main.Class2 contains methods)
	// Class1 | Class2

	struct{ S string }
	// EqString

	// In a term of the form ~T, the underlying type of T must be itself, and T cannot be an interface.
	// ~SString

	Class3

	InterfaceMethod(c int)
}

// NonDerivableString is a copy of C, except no derived types are allowed
type NonDerivableString interface {
	// cannot use main.Class1 in union (main.Class1 contains methods)
	// cannot use main.Class2 in union (main.Class2 contains methods)
	// Class1 | Class2

	// struct{S string}
	EqString

	// In a term of the form ~T, the underlying type of T must be itself, and T cannot be an interface.
	// ~SString

	Class3

	InterfaceMethod(c int)
}

type DerivedString struct {
	S string
}

type EqString = struct {
	S string
}

type DerivedEqString EqString

var _ Class1 = DerivedEqString{}
var _ Class2 = DerivedEqString{}
var _ Class3 = DerivedEqString{}

// interface contains type constraints
// var _ DerivableStruct = DerivedEqString{}

func (d DerivedEqString) Method1(a int) {
	fmt.Println("D.Method1", d, a)
}

func (d DerivedEqString) Method2(b int) {
	fmt.Println("D.Method2", d, b)
}

func (d DerivedEqString) Method3(c int) {
	fmt.Println("D.Method3", d, c)
}

func (d DerivedEqString) InterfaceMethod(c int) {
	fmt.Println("D.InterfaceMethod", d, c)
}

// This will not work with NonDerivableString because you cannot add methods to another struct
type EqEqString = EqString

// invalid receiver type struct{S string}
// func (es EqString) Method3(x int) {
// 	fmt.Println("EqString.Method3", es, x)
// }

// invalid receiver type struct{S string}
// func (ees EqEqString) X(x int) {
// 	fmt.Println("EqEqString.X", ees, x)
// }

// func (ees EqEqString) InterfaceMethod(c int) {
// 	fmt.Println("EqEqString.C", ees, c)
// }

type DerivedDerivedString DerivedString

func (e DerivedDerivedString) Method2(b int) {
	fmt.Println("E.Method2", e, b)
}

func (e DerivedDerivedString) InterfaceMethod(c int) {
	fmt.Println("E.InterfaceMethod", e, c)
}

func (e DerivedDerivedString) Method3(x int) {
	fmt.Println("E.Method3", e, x)
}

type DerivedStruct struct {
	S string
}

func (f DerivedStruct) InterfaceMethod(c int) {
	fmt.Println("F.InterfaceMethod", f, c)
}

func (f DerivedStruct) Method3(x int) {
	fmt.Println("F.Method3", f, x)
}

// interface contains type constraints
// func AcceptInterfaceMethod(c DerivableStruct) {
// 	fmt.Println("Calling AcceptC")
// 	c.Method3(123)
// 	fmt.Println()
// }

func AcceptInterfaceMethod[T DerivableStruct](c T) {
	fmt.Println("Calling AcceptInterfaceMethod")
	c.Method3(123)
	fmt.Println()
}

// eq.S undefined (type T has no field or method S
// func AcceptEqString[T ~struct{ S string }](eq T) {
// 	fmt.Println("EqString.S", eq.S)
// }

func AcceptEqString[T ~struct{ S string }](eq T) {
	// Needs conversion.
	fmt.Println("EqString.S", struct{ S string }(eq).S)
}

func AcceptDerivableStruct[T DerivableStruct](c T) {
	fmt.Println("Calling AcceptInterfaceMethod")
	// Not for interfaces.
	// cannot use interface DerivableStruct in conversion (contains specific type constraints or is comparable)
	// fmt.Println("DerivableStruct.S", DerivableStruct(c).S)
	c.Method3(123)

	AcceptDerivableString(c)
}

func AcceptDerivableString[T DerivableString](c T) {
	fmt.Println("Calling AcceptDerivableString")
	// Needs to really find the root of the type that has a method S
	fmt.Println("AcceptDerivableString.S", EqString(c).S)
	c.Method3(123)
	fmt.Println()
}

func AcceptNonDerivableStruct[T NonDerivableStruct](c T) {
	fmt.Println("Calling AcceptNonDerivableStruct")
	fmt.Println("AcceptNonDerivableStruct.S", EqString(c).S)
	c.Method3(123)

	AcceptDerivableString(c)
}

func AcceptNonDerivableString[T NonDerivableString](c T) {
	fmt.Println("Calling AcceptNonDerivableString")
	AcceptNonDerivableStruct(c)
}

func main() {
	d := DerivedEqString{S: "d"}
	e := DerivedDerivedString{S: "e"}
	f := DerivedStruct{S: "f"}

	AcceptDerivableStruct(d)
	AcceptDerivableStruct(e)
	AcceptDerivableStruct(f)

	AcceptEqString(d)

	// struct{S string} does not implement NonDerivableStruct (missing method InterfaceMethod)
	// AcceptNonDerivableStruct(EqEqString{S: "dd"})

	// struct{S string} does not implement DerivableStruct (missing method InterfaceMethod)
	// AcceptDerivableStruct(EqEqString{S: "dd"})
}
