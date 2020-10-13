package main

type someStruct struct {
	a int
}

func (ss someStruct) String() {
	println("called")
}

func callReceiver(f func(someStruct), ss someStruct) {
	f(ss)
}

func callValue(f func()) {
	f()
}

func main() {
	ss := &someStruct{}
	ss.String()

	callReceiver(someStruct.String, *ss)
	callValue(ss.String)
}
