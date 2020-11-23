using System;
using System.Diagnostics;
namespace C_
{
    class PrimeNumbers
    {
        public static bool IsPrime(int num)
        {
            if (num == 2) return true;
            if (num <= 1 || num % 2 == 0) return false;
            double sqrt_num = Math.Sqrt(num);
            for (int div = 3; div <= sqrt_num; div += 2)
            {
                if (num % div == 0) return false;
            }
            return true;
        }
        static void Main(string[] args)
        {
            Stopwatch stopwatch = new Stopwatch();
            long N = 10000000;
            stopwatch.Start();
            for (int i = 0; i < N; i++) IsPrime(i);
            stopwatch.Stop();
            Console.WriteLine(stopwatch.Elapsed.TotalSeconds);
        }
    }
}