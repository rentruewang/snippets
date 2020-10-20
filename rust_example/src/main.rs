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

fn main() {
    let t = Type;

    t.call();
    Type::call(&t);

    somef1(Type::call, &t);

    // let c = t.call;
    // somef2(c);
}
