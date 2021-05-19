use async_std::task;
use futures::{executor, Future};
use std::time::Duration;

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

fn somef2<F>(f: F)
where
    F: Fn(),
{
    f()
}

trait Bad {
    fn generic_method<A>(&self, value: A);
}

fn _func<T: Bad + ?Sized>(x: &T) {
    x.generic_method("foo"); // A = &str
    x.generic_method(1_u8); // A = u8
}

trait Any {}

struct A;

impl Any for A {}

struct B;

impl Any for B {}

fn thin<T: Any>(_: T) {}
fn fat1<T: Any + ?Sized>(_: &T) {}
fn fat2(_: &dyn Any) {}

fn main() {
    let t = Type;

    t.call();
    Type::call(&t);

    somef1(Type::call, &t);

    let c = t.call;
    somef2(c);

    let mut any: &dyn Any;
    any = &A;
    let _a = any;
    any = &B;
    let _b = any;
    fat1(any);
    fat2(any);
    thin(A);
    thin(B);

    noreturn1();
    noreturn2();

    executor::block_on(async {
        futures::join!(blocks(), move_block());
    });

    let v: Vec<_> = vec![1, 2, 3]
        .into_iter()
        .flat_map(|x| vec![x, x + 1])
        .collect();

    println!("{:?}", v);
}

fn noreturn1() {()}

fn noreturn2() {}

async fn blocks() {
    let my_string = "1".to_string();

    let future_one = async {
        println!("{} 1", my_string);
    };

    let future_two = async {
        task::sleep(Duration::from_secs(2)).await;
        println!("{} 2", my_string);
    };

    let future_three = async {
        task::sleep(Duration::from_secs(3)).await;
        println!("{} 3", my_string);
    };

    futures::join!(
        async {
            let x = future_one;
            future_three.await;
            x.await;
        },
        future_two
    );
}

fn move_block() -> impl Future<Output = ()> {
    let my_string = "2".to_string();
    async move {
        task::sleep(Duration::from_secs(1)).await;
        println!("{}", my_string);
    }
}
