pub trait Trait {
    fn do_something(&self);
}

pub trait TraitSized: Sized {
    fn do_something(&self);
}

pub struct A {}

impl A {
    fn dispatch(self, other: impl Methods) {
        println!("Member method!");
        other.bound_method();
    }
}

impl Trait for A {
    fn do_something(&self) {
        println!("A");
    }
}

impl TraitSized for A {
    fn do_something(&self) {
        (self as &dyn Trait).do_something()
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

impl TraitSized for B {
    fn do_something(&self) {
        (self as &dyn Trait).do_something()
    }
}

pub trait Methods: Sized {
    fn static_method() {
        println!("static method in trait is ok")
    }

    fn bound_method(&self) {
        println!("bound method in trait is always ok")
    }
}

impl Methods for A {}
impl Methods for B {}

pub trait DynamicDispatch: Sized {
    fn static_take_trait_obj(obj: impl Methods) {
        obj.bound_method();
    }

    fn bound_take_trait_obj(&self, obj: impl Methods) {
        obj.bound_method();
    }

    fn dispatch<F>(&self, obj: F)
    where
        F: Methods + Sized,
    {
        println!("dispatch method (sized)");
        obj.bound_method();
    }
}

impl DynamicDispatch for A {}
impl DynamicDispatch for B {}

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

    let vec: Vec<Box<dyn Trait>> = vec![
        Box::new(A {}),
        Box::new(A {}),
        Box::new(B { something: 3 }),
        Box::new(A {}),
        Box::new(B { something: 5 }),
        Box::new(B { something: 4 }),
    ];

    for elem in vec.iter() {
        elem.do_something();
    }

    // let vec: Vec<Box<dyn TraitSized>> = vec![
    //     Box::new(A {}),
    //     Box::new(A {}),
    //     Box::new(B { something: 3 }),
    //     Box::new(A {}),
    //     Box::new(B { something: 5 }),
    //     Box::new(B { something: 4 }),
    // ];

    // for elem in vec.iter() {
    //     elem.do_something();
    // }

    B::static_method();
    A {}.bound_method();
    // A {}.static_method();
    Methods::bound_method(&A {});
    // Calling method on trait is not ok
    // Methods::static_method();
    A::static_take_trait_obj(A {});
    A {}.bound_take_trait_obj(B { something: 3 });
    A {}.dispatch(B { something: 4 });
    A {}.dispatch(B { something: 4 });

    println!("as dd");
    A {}.dispatch(A {});
    <A as DynamicDispatch>::dispatch(&A {}, A {});
}
