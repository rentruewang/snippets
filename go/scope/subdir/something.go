package subdir

type Something struct {
	privateField int
}

func (sth Something) PrivateField() int {
	return sth.privateField
}
