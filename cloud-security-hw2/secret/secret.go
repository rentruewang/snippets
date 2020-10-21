// Package p contains an HTTP Cloud Function.
package p

import (
	"fmt"
	"io/ioutil"
	"log"
	"math/rand"
	"net/http"
)

func Handler(w http.ResponseWriter, r *http.Request) {
	secrets := []string{
		"London",
		"Paris",
		"Berlin",
		"NewYork",
		"Beijing",
		"Cairo",
		"Buenos Aires",
		"Moskva",
		"Taipei",
	}

	l := len(secrets)

	dat, err := ioutil.ReadAll(r.Body)
	if err != nil {
		log.Fatal(err)
	}
	data := string(dat)

	var s string

	switch r.Method {
	case http.MethodGet:
		rd := rand.Intn(l)
		s = secrets[rd]
		log.Println("GET", l)
	case http.MethodPost:
		secrets = append(secrets, data)
		s = data
		log.Println("POST", l)
	case http.MethodDelete:
		j := 0
		for i := 0; i < len(secrets); i++ {
			if secrets[i] == data {
				j = i
				break
			}
		}
		secrets[j], secrets[l-1] = secrets[l-1], secrets[j]
		secrets = secrets[:l-1]

		rd := rand.Intn(len(secrets))
		s = secrets[rd]
		log.Println("DELETE", l)
	}
	log.Println("after processing:", secrets)

	fmt.Fprintln(w, s)
}
