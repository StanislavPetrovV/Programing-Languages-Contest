use criterion::{black_box, criterion_group, criterion_main, Criterion};
use rayon::prelude::*;

const N: i32 = 10000000;

fn is_prime(num: f32) -> bool {
    if num == 2. {
        true
    } else if num <= 1. || (num % 2.) == 0. {
        false
    } else {
        // let to = (num as f32).sqrt() as i32;
        let mut div = 3.;
        while div <= num.sqrt() {
            if (num % div) == 0. {
                return false;
            }
            div += 2.;
        }
        true
    }
}

fn is_prime_bench(c: &mut Criterion) {
    c.bench_function("is_prime 10000000", |b| {
        b.iter(|| {
            (0..N).into_par_iter().for_each(|x| {
                is_prime(black_box(x as f32));
            })
        })
    });
}

criterion_group!(benches, is_prime_bench);
criterion_main!(benches);
