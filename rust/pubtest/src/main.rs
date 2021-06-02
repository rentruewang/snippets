mod file;

use file::Struct;

fn main() {
    println!("Hello, world!");

    // This line fails because you cannot access private fields.
    // let s = Struct {
    //     field1: 1,
    //     field2: 2,
    // };

    // let s = Struct {};

    // println!("{}", s.field1);
    // println!("{}", s.field2);
}
