#[derive(Copy, Clone)]
struct Type;

impl Type {
    fn call(&self) {
        println!("hello")
    }
}

fn somef1<F>(f: F, t: &Type)
where
    F: Fn(&Type),
{
    f(t)
}

// fn somef2<F>(f: F)
// where
//     F: Fn(),
// {
//     f()
// }

trait Bad {
    fn generic_method<A>(&self, value: A);
}

fn func<T: Bad + ?Sized>(x: &T) {
    x.generic_method("foo"); // A = &str
    x.generic_method(1_u8); // A = u8
}

fn main() {
    let t = Type;

    t.call();
    Type::call(&t);

    somef1(Type::call, &t);

    // let c = t.call;
    // somef2(c);
}
