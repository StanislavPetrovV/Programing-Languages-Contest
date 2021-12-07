package main

import (
	"fmt"
	"math"
	"sync"
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

const threads = 4
const n = 10000000
const nByThread = n / threads

func worker(id int, wg *sync.WaitGroup) {
	start := id * nByThread
	end := start + nByThread
	for i := start; i < end; i++ {
		isPrime(i)
	}
	wg.Done()
}

func main() {
	wg := sync.WaitGroup{}
	wg.Add(threads)
	start := time.Now()
	for i := 0; i < threads; i++ {
		go worker(i, &wg)
	}
	wg.Wait()
	fmt.Println(time.Since(start))
}
