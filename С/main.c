//Си реализация многопоточного выполнения алгоритма в среде Windows.
//Алгоритм работает в 4 потока. Количество потоков легко расширяемо.

///////////////////TIMER///////////////////

//Очень точный таймер, возвращающий время в секундах.

//	StartTimer();
//	*работа алгоритма*
//	double time = StopTimer();

#include <windows.h>

static LONGLONG	cntsPerSec, t1, t2;
static double	secsPerCnt;

void StartTimer(void)
{
	QueryPerformanceFrequency((LARGE_INTEGER *) &cntsPerSec);
	secsPerCnt = 1./cntsPerSec;
	QueryPerformanceCounter((LARGE_INTEGER *) &t1);
}

double StopTimer(void)
{
	QueryPerformanceCounter((LARGE_INTEGER *) &t2);
	
	return secsPerCnt * (t2 - t1);
}

///////////////////IS PRIME///////////////////

#include <math.h>

//Алгоритмически функция полностью эквивалентна той, что представлена в видео.
unsigned isPrime(unsigned n)
{
	if(n == 2)
		return 1;
		
	if(!(n > 1 && n % 2))
		return 0;
	
	unsigned sqrtn = sqrt(n), div = 1;
	
	while((div += 2) <= sqrtn && n % div)
		;
	
	return div > sqrtn;
}

///////////////////THREAD FUNCTION///////////////////

#include <process.h>

//При запуске потока в качестве аргумента ему можно передать только указатель.
//Так, передав указатель на структуру, поток получит все необходимые данные.
typedef struct {
	unsigned l;	//Левая  граница проверяемых чисел.
	unsigned r;	//Правая граница проверяемых чисел.
	unsigned f;	//Флаг, сигнализирующий о завершении потока.
	unsigned n;	//Количество простых чисел, найденных в потоке.
} ARGUMENT, *LPARGUMENT;

//Количество потоков. При изменении нужно инициализировать соответствующее
//количество аргументов в функции main() (см. ARGUMENT A[THREADS_NUM]).
#define THREADS_NUM 4

//Функция для выполнения в отдельном потоке.
unsigned _stdcall ThreadFunc(void *voidArg)
{
	LPARGUMENT arg = (LPARGUMENT) voidArg;
	
	for(; arg->l <= arg->r; ++arg->l)
		arg->n += isPrime(arg->l);
	
	//Сигнал о завершении данного потока
	return arg->f = 1;
}

///////////////////MAIN FUNCTION///////////////////

#include <stdio.h>

int main(void)
{
	//Количество аргументов должно равняться количеству потоков (THREADS_NUM).
	volatile ARGUMENT A[THREADS_NUM] = {
	//   l        r         f  n
		{1      , 4000000 , 0, 0},
		{4000001, 6000000 , 0, 0},
		{6000001, 8000000 , 0, 0},
		{8000001, 10000000, 0, 0},
	};
	
	//Запуск таймера.
	StartTimer();
	
	//Запуск потоков. Здесь:
	//1. ThreadFunc - указатель на функцию для выполнения в отдельном потоке.
	//2. A + i      - аргумент для ThreadFunc, указатель на i-тую структуру для i-того потока.
	{
		int i;
		for(i = 0; i < THREADS_NUM; ++i)
			_beginthreadex(NULL, 0, ThreadFunc, (void *) (A + i), 0, NULL);
	}
	
	//Ожидание завершения всех потоков.
	{
		int i, s = 0;
		while(s < THREADS_NUM)
			for(s = i = 0; i < THREADS_NUM; ++i)
				s += A[i].f;
	}
	
	//Время работы.
	printf("Time\t= %.4lf\n", StopTimer());
	
	//Общее количество найденных простых чисел.
	int primes = 0;
	
	{
		int i;
		for(i = 0; i < THREADS_NUM; ++i)
			primes += A[i].n;
	}
	
	printf("Primes\t= %u", primes);
	
	return 0;
}