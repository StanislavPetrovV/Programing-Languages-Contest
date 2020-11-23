#include <iostream>
#include <cmath>
#include <time.h>
#include <thread>

bool isPrime(int num)
{
if (num == 2) return true;
else if (num <= 1 || num % 2 == 0) return false;
double sqrt_num = sqrt(double(num));
for (int div = 3; div <= sqrt_num; div += 2) {
if (num % div == 0) return false;
}
return true;
}

void start_multithreading(int n, int x) {
for (; x < n; x += 4) isPrime(x);
}

int main() {
const int PROCESSOR_COUNT = std::thread::hardware_concurrency();
int n = 10000000;

std::thread threads[4]{
std::thread(start_multithreading, n, 0),
std::thread(start_multithreading, n, 1),
std::thread(start_multithreading, n, 2),
std::thread(start_multithreading, n, 3)
};



clock_t start, end;
start = clock();

threads[0].join();
threads[1].join();
threads[2].join();
threads[3].join();

end = clock();
printf("time: %f", (end - start) / ((double)CLOCKS_PER_SEC));
// scanf_s("%i", &n);
return 0;
}