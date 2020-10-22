// Package p contains an HTTP Cloud Function.
package p

import (
	"fmt"
	"io"
	"io/ioutil"
	"net/http"
)

func Handler(w http.ResponseWriter, r *http.Request) {

	var input string

	if i, err := ioutil.ReadAll(r.Body); err != nil {
		switch err {
		case io.EOF:
			input = "{}"
		default:
			fmt.Println("Premature return because of read error:", err)
			return
		}
	} else {
		input = string(i)
	}

	if output, err := process(input); err == nil {
		fmt.Fprintln(w, output)
	} else {
		fmt.Println("Premature return because of process error:", err)
		return
	}
}
