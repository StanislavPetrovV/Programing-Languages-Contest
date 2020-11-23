package main

import (
	"fmt"
	"math"
	"time"
)

func isPrime(num int) bool {
	if num == 2 {
		return true
	}
	if num <= 1 || (num%2) == 0 {
		return false
	}
	for div := 3; div <= int(math.Sqrt(float64(num))); div += 2 {
		if (num % div) == 0 {
			return false
		}
	}
	return true

}

func main() {
	N := 10000000
	start := time.Now()
	for i := 0; i < N; i++ {
		go isPrime(i)
	}
	fmt.Println(time.Since(start))
	fmt.Scanln()
}
