// https://stackoverflow.com/questions/27831944/how-do-i-store-a-closure-in-a-struct-in-rust

// Unboxed, generic.
struct Foo1<F>
where
    F: Fn(usize) -> usize,
{
    pub foo1: F,
}

impl<F> Foo1<F>
where
    F: Fn(usize) -> usize,
{
    fn new(foo1: F) -> Self {
        Self { foo1 }
    }
}

// Boxed, trait.
struct Foo2 {
    pub foo2: Box<dyn Fn(usize) -> usize>,
}

impl Foo2 {
    fn new(foo2: impl Fn(usize) -> usize + 'static) -> Self {
        Self {
            foo2: Box::new(foo2),
        }
    }
}

// Reference, trait.
struct Foo3<'a> {
    pub foo3: &'a dyn Fn(usize) -> usize,
}

impl<'a> Foo3<'a> {
    fn new(foo3: &'a dyn Fn(usize) -> usize) -> Self {
        Self { foo3 }
    }
}

struct Foo4 {
    pub foo4: fn(usize) -> usize,
}

impl Foo4 {
    fn new(foo4: fn(usize) -> usize) -> Self {
        Self { foo4 }
    }
}

fn main() {
    let foo1 = Foo1 { foo1: |a| a + 1 };
    (foo1.foo1)(42);
    (Foo1::new(|a| a + 1).foo1)(42);

    let foo2 = Foo2 {
        foo2: Box::new(|a| a + 1),
    };
    (foo2.foo2)(43);
    (Foo2::new(|a| a + 1).foo2)(43);

    let foo3 = Foo3 { foo3: &|a| a + 1 };
    (foo3.foo3)(44);
    (Foo3::new(&|a| a + 1).foo3)(44);

    let foo4 = Foo4 { foo4: |a| a + 1 };
    (foo4.foo4)(45);
    (Foo4::new(|a| a + 1).foo4)(45);

    // closures can only be coerced to `fn` types if they do not capture any variables
    let x = 3_usize;
    // let f1: fn() -> usize = || x;
    // println!("{}", f1());
    let f2: &dyn Fn() -> usize = &|| x;
    println!("{}", f2());
}
