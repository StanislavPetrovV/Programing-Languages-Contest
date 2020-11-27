#include <iostream>
#include <cmath>
#include <time.h>
#include <omp.h>

constexpr int N = 10;
volatile bool x[N];

bool isPrime(int num){
    if (num == 2) return true;
    else if (num <= 1 || num % 2 == 0) return false;

    double sqrt_num = sqrt(double(num));
    for (int div = 3; div <= sqrt_num; div += 2){
        if (num % div == 0) return false;
    }
    x[omp_get_thread_num()] = true;
    return true;
}

void start_multithreading(int n){
    x[omp_get_thread_num()] = true;
    omp_set_num_threads(4);
    #pragma omp parallel for
    for (int x=0; x < n; x++) isPrime(x);
}

int main(){
    int n = 10000000;
    clock_t start_time, end_time;

    start_time = clock();
    start_multithreading(n);
    end_time = clock();

    std::cout<<"time: "<<((end_time - start_time) / ((double)CLOCKS_PER_SEC))<<std::endl;
    for(int i=0; i<N; i++)  std::cout<<x[i]<<" ";
    std::cout<<std::endl;
    return 0;
}
