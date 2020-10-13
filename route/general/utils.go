package general

import "errors"

// PairInt contains a pair of values
type PairInt struct {
	X, Y int
}

// NewPairInt is a constructor for PairInt
func NewPairInt(x, y int) *PairInt {
	return &PairInt{X: x, Y: y}
}

// Location represents a cell's location. By default it's 2d
type Location struct{ PairInt }

// NewLocation is a constructor for Location
func NewLocation(x, y int) *Location {
	return &Location{PairInt{x, y}}
}

// ErrNoSegment indicates that the segment is not a segment
var ErrNoSegment = errors.New("This is not a segment")

// Segment is a strait line between different that is parallel to either X, Y or Z axis
type Segment struct {
	A, B Location
}

// IsValid checks whether the segment is valid
func (seg Segment) IsValid() bool {
	return (seg.A.X == seg.B.X) != (seg.A.Y == seg.B.Y)
}

// Validate throws an error if the segment is not valid
func (seg Segment) Validate() error {
	if seg.IsValid() {
		return nil
	}
	return ErrNoSegment
}

// Net holds segments
type Net struct {
	nodes []Segment
}

