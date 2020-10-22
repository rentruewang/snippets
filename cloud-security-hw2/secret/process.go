package p

import (
	"encoding/json"
	"errors"
	"io"
	"math/rand"
)

var secrets = []string{
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

func process(input string) (output string, err error) {
	if input == "" {
		err = io.EOF
		return
	}

	contents := make(map[string]string)
	json.Unmarshal([]byte(input), &contents)

	if input == "{}" {
		if len(contents) == 0 {
			rd := rand.Intn(len(secrets))
			output = secrets[rd]
		} else {
			err = errors.New("Wierd that input is {} but get something as return")
		}
		return
	}

	if _, ok := contents["list"]; ok {
		var o []byte
		o, err = json.Marshal(map[string]interface{}{
			"data": secrets,
		})
		output = string(o)
		return
	}

	if val, ok := contents["add"]; ok {
		skip := false
		for i := 0; i < len(secrets); i++ {
			if secrets[i] == val {
				skip = true
				break
			}
		}
		if !skip {
			secrets = append(secrets, val)
		}

		return
	}

	if val, ok := contents["del"]; ok {
		i := 0
		for i = 0; i < len(secrets); i++ {
			if secrets[i] == val {
				break
			}
		}
		last := len(secrets) - 1
		secrets[i], secrets[last] = secrets[last], secrets[i]
		secrets = secrets[:last]

		if len(secrets) == 0 {
			output = "here"
			return
		}

		rd := rand.Intn(len(secrets))
		output = secrets[rd]

		return
	}

	return
}
