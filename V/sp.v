module main

import benchmark
import math

pub fn is_prime(num int) bool {
	if num == 2 {
		return true
	}
	if num <= 1 || (num%2) == 0 {
		return false
	}
	num_sqrt := math.sqrt(f64(num))
	for div := 3; div <= num_sqrt; div += 2 {
		if (num % div) == 0 {
			return false
		}
	}
	return true
}

/*
~ 5.06 ms on i3-2120
build with v -prod sp.v
*/
fn main(){
	n := 10000000
	mut b := benchmark.start()
	for i := 0; i < n; i++ {
		is_prime(i)
	}
	b.measure('code_1')
}