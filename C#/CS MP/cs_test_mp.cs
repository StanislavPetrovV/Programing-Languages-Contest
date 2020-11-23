using System;
using System.Diagnostics;
using System.IO;
using System.Threading.Tasks;

class Program
{
    public static bool IsPrime(int num)
    {
        if (num == 2) return true;
        if (num <= 1 || num % 2 == 0) return false;

        double sqrt_num = Math.Sqrt(num);
        for (int div = 3;  div <= sqrt_num; div += 2)
        {
            if (num % div == 0) return false;
        }
        
        return true;
        
    }

    public static void Main(string[] args)
    {
        Stopwatch stopwatch = new Stopwatch();
        int N = 10000000;
        stopwatch.Start();
        Parallel.For(0, N, new ParallelOptions { MaxDegreeOfParallelism = 4 }, index =>  
        { 
            IsPrime(index);
        });
            
        
        stopwatch.Stop();
        Console.WriteLine(stopwatch.Elapsed.TotalSeconds);
    }
}


