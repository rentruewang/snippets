package main

import (
	"fmt"
	"runtime/debug"
	"time"
)

type Item struct{ Title, Channel, GUID string }

// Fetcher is what we have.
type Fetcher interface {
	Fetch(url string) (items []Item, next time.Time, err error)
}

func Fetch(domain string) Fetcher { return nil }

// Subscription is what we want.
type Subscription interface {
	// Updates receive a stream of items.
	Updates() <-chan Item

	// Cancel stops the subscription.
	Cancel() error
}

func Subscribe(fetcher Fetcher) Subscription {
	s := sub{fetcher: fetcher, updates: make(chan Item)}
	go s.loop()
	return s
}
func Merge(subs ...Subscription) Subscription { return nil }

func main() {
	// This code will definitely panic because those interfaces are never implemented.
	merged := Merge(
		Subscribe(Fetch("https://go.dev/blog/")),
		Subscribe(Fetch("https://blog.google/")),
	)

	time.AfterFunc(3*time.Second, func() {
		fmt.Println("Closed:", merged.Cancel())
	})

	for it := range merged.Updates() {
		fmt.Println(it.Channel, it.Title)
	}

	debug.PrintStack()

	panic("Show me the stacks")
}

type sub struct {
	fetcher Fetcher
	updates chan Item
}

func (s sub) loop() {}

func (s sub) Updates() <-chan Item {
	return s.updates
}

func (s sub) Cancel() error {
	// TODO: loop exit and find error.
	close(s.updates)
	return nil
}

type badSub struct {
	sub

	closed bool
	err    error
}

func (bs *badSub) loop() {
	for {
		// FIXME: closed have datarace between loop and Cancel
		// detected by go run -race .
		if bs.closed {
			close(bs.updates)
			return
		}

		items, next, err := bs.fetcher.Fetch("")
		if err != nil {
			// FIXME: err have datarace between loop and Cancel
			// detected by go run -race .
			bs.err = err
			time.Sleep(10 * time.Second)
			continue
		}

		for _, item := range items {
			bs.updates <- item
		}

		if now := time.Now(); next.After(now) {
			time.Sleep(next.Sub(now))
		}
	}
}

func (bs *badSub) Cancel() error {
	bs.closed = true
	return bs.err
}
