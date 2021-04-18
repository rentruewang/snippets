pub trait Trait {
    fn do_something(&self);
}

pub struct A {}

impl Trait for A {
    fn do_something(&self) {
        println!("A");
    }
}

pub struct B {
    something: isize,
}

impl Trait for B {
    fn do_something(&self) {
        println!("B {}", self.something);
    }
}

fn main() {
    // This part does not work because the size of A and B can be unequal,
    // so rust forbids adding raw trait objects

    // let mut vec: Vec<dyn Trait> = vec![];
    // vec.push(A {});
    // vec.push(A {});
    // vec.push(A {});
    // vec.push(B { something: 3 });
    // vec.push(B { something: 4 });

    // for elem in vec.iter() {
    //     elem.do_something();
    // }

    let mut vec: Vec<Box<dyn Trait>> = vec![];

    vec.push(Box::new(A {}));
    vec.push(Box::new(A {}));
    vec.push(Box::new(A {}));

    vec.push(Box::new(B { something: 3 }));
    vec.push(Box::new(B { something: 4 }));
    vec.push(Box::new(B { something: 5 }));

    for elem in vec.iter() {
        elem.do_something();
    }
}
