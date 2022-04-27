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

	// closing is like a server. When a channel is received (Cancel called),
	// it closes down the subscription, and then send the error that is encountered
	// back by the channel that closing just received (or nil).
	closing chan chan error
}

func (s sub) loop() {
	var err error
	for {
		select {
		case errc := <-s.closing:
			// send updates
			errc <- err
			// done
			close(s.updates)
			return
		}
	}
}

func (s sub) Updates() <-chan Item {
	return s.updates
}

func (s sub) Cancel() error {
	// TODO: loop exit and find error.
	errc := make(chan error)
	s.closing <- errc
	return <-errc
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
			// FIXME: If client is closed and doesn't receive from the channel,
			// this line will cause the loop to hang forever.
			bs.updates <- item
		}

		if now := time.Now(); next.After(now) {
			// FIXME: time.Sleep keeps this goroutine alive.
			// This is (sort of) a memory leak.
			time.Sleep(next.Sub(now))
		}
	}
}

func (bs *badSub) Cancel() error {
	bs.closed = true
	return bs.err
}
