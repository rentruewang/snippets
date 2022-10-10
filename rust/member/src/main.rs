struct Something {
    member: usize,
}

impl Something {
    fn method1(&self, other: &Self) {
        println!("method 1: {} {}", self.member, other.member);
    }

    fn method2(first: &Self, second: &Self) {
        println!("method 2: {} {}", first.member, second.member);
    }
}

fn main() {
    let first = Something { member: 23 };
    let second = Something { member: 42 };

    Something::method1(&first, &second);
    Something::method2(&first, &second);

    first.method1(&second);
    // this is an associated function, not a method
    // first.method2(&second);
}
