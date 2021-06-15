fn main() {
    // closures can only be coerced to `fn` types if they do not capture any variables
    let x = 3_usize;
    // let f: fn() -> usize = || x;
    let f: &Fn() -> usize = &|| x;
    println!("{}", f());
}
