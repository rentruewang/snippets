package main

import (
	"encoding/csv"
	"fmt"
	"io"
	"log"
	"strings"
)

func main() {
	in := `id,first_name,last_name,username
0,"Rob","Pike",rob
1,Ken,Thompson
2, "Robert","Griesemer","gri"
`
	fmt.Println(io.ReadAll(strings.NewReader(in)))

	r := csv.NewReader(strings.NewReader(in))
	r.LazyQuotes = true

	records, err := r.ReadAll()
	if err != nil {
		log.Fatalln(err)
	}

	fmt.Print(records)
}
