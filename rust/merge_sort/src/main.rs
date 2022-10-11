use std::fmt::Debug;

use num::Num;

fn merge_sort<T: Num + Copy + Ord + Debug>(seq: &[T]) -> Vec<T> {
    let length = seq.len();

    if length <= 1 {
        return seq.to_vec();
    }

    let half = length / 2;

    let first_half = &merge_sort(&seq[..half]);
    let second_half = &merge_sort(&seq[half..]);

    merge(first_half, second_half)
}

fn merge<T: Num + Copy + Ord + Debug>(mut a: &[T], mut b: &[T]) -> Vec<T> {
    let mut result = Vec::with_capacity(a.len() + b.len());

    while !a.is_empty() && !b.is_empty() {
        if a[0] < b[0] {
            result.push(a[0]);
            a = &a[1..];
        } else {
            result.push(b[0]);
            b = &b[1..];
        }
    }

    for &remain in a {
        result.push(remain)
    }

    for &remain in b {
        result.push(remain);
    }

    result
}

fn main() {
    let vector = vec![3, 24, 25, 231, 4, 25, 7, 3];
    println!("{:?}", merge_sort(&vector));
}
