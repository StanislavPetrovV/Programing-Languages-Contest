extern crate time;
use time::PreciseTime;
use std::io::{stdin, stdout, Read, Write};

fn is_prime(num: i32) -> bool {
    if num == 2 {
        return true;
    }
    if num <= 1 || (num%2) == 0 {
		return false;
	}
	let to = (num as f64).sqrt() as i32;
	let mut div = 3;
	while div <= to {
		if (num % div) == 0 {
			return false
		}
		div += 2;
	}
	return true;
}


fn main() {
    let n = 10000000;
    let start = PreciseTime::now();
    for x in 0..n {
        is_prime(x);
    }
    let end = PreciseTime::now();
    println!("{} seconds", start.to(end).as_seconds_f32());
    let mut stdout = stdout();
    stdout.write(b"").unwrap();
    stdout.flush().unwrap();
    stdin().read(&mut [0]).unwrap();
}
