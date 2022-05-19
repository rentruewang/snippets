package main

import (
	"fmt"
	"runtime/debug"
	"time"
)

type Item struct{ Title, Channel, GUID string }

// Fetcher is what we have.
type Fetcher interface {
	Fetch() (items []Item, next time.Time, err error)
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

	// closing is like a server. It's called a reply channel.
	// When a channel is received (Cancel called),
	// it closes down the subscription, and then send the erro
	// back by the channel that closing just received (or nil).
	closing chan chan error
}

func (s sub) loop() {
	var pending []Item
	var next time.Time
	var err error

	for {
		// For fetch part
		var fetchDelay time.Duration
		if now := time.Now(); next.After(now) {
			fetchDelay = next.Sub(now)
		}

		doFetch := time.After(fetchDelay)

		// For send part
		var first Item
		var updates chan Item
		if len(pending) == 0 {
			first = pending[0]
			updates = s.updates
		}

		select {
		// Case 1: CLose
		case errc := <-s.closing:
			// send updates
			errc <- err
			// done
			close(s.updates)
			return
		// Case 2: Fetch
		// FIXME: If subscriber doens't receive for a long time, pending may get large.
		// So we are bounding pending items (by diabling doFetch if pending is too big).
		case <-doFetch:
			var fetched []Item
			// FIXME: Fetch is an IO operation, could take a really long time.
			// Because it's blocking (sequential), during which the loop would be unresponsive.
			fetched, next, err = s.fetcher.Fetch()
			if err != nil {
				next = time.Now().Add(10 * time.Second)
				break
			}
			// FIXME: There could be seen items in fetched items.
			pending = append(pending, fetched...)
		// Case 3: Send
		case updates <- first:
			pending = pending[1:]
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

		items, next, err := bs.fetcher.Fetch()
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

type goodSub struct {
	sub
}

type fetchResult struct {
	fetched []Item
	next    time.Time
	err     error
}

func (gs goodSub) loop() {
	var pending []Item
	var seen = make(map[string]bool)
	var fetchDone chan fetchResult
	var result = fetchResult{}

	for {
		// For fetch part
		var fetchDelay time.Duration
		if now := time.Now(); result.next.After(now) {
			fetchDelay = result.next.Sub(now)
		}

		// doFetch := time.After(fetchDelay)

		var doFetch <-chan time.Time
		// Enable fetch only when we're not fetching.
		if fetchDone == nil && len(pending) < 10 {
			doFetch = time.After(fetchDelay)
		}

		// For send part
		var first Item
		var updates chan Item
		if len(pending) == 0 {
			first = pending[0]
			updates = gs.updates
		}

		select {
		// Case 1: CLose
		case errc := <-gs.closing:
			// Send updates
			errc <- result.err
			// Done
			close(gs.updates)
			return
		// Case 2: Fetch
		case result = <-fetchDone:
			fetchDone = nil

			if result.err != nil {
				result.next = time.Now().Add(10 * time.Second)
				break
			}

			// pending = append(pending, fetched...)

			for _, item := range result.fetched {
				if !seen[item.GUID] {
					pending = append(pending, item)
					seen[item.GUID] = true
				}
			}
		// Case 3: Send
		case updates <- first:
			pending = pending[1:]
		// Case 4: Wait for fetch
		case <-doFetch:
			fetchDone = make(chan fetchResult)

			go func() {
				fetched, next, err := gs.fetcher.Fetch()
				fetchDone <- fetchResult{fetched: fetched, next: next, err: err}
			}()
		}
	}
}

func (gs goodSub) Updates() <-chan Item {
	return gs.Updates()
}

func (gs goodSub) Cancel() error {
	return gs.sub.Cancel()
}
