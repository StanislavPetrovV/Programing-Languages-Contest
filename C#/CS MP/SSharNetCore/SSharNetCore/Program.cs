using System;
using System.Diagnostics;
using System.Threading.Tasks;

namespace SSharNetCore
{
  class Program
  {
    const long N = 10000000; //10000000

    static Stopwatch time = new Stopwatch();

    static void Main(string[] args)
    {

      ///Foo(); //последовательный
      Foo3();

      Console.ReadKey();
    }

    static void Foo()
    {
      time.Start();
      Console.WriteLine("Start");
      for (int i = 0; i < N; i++)
      {
        isPrime(i);
      }
      time.Stop();
      TimeSpan ts = time.Elapsed;
      Console.WriteLine(ts.ToString("mm\\:ss\\.ff"));
      Console.WriteLine("End");
    }

    static bool isPrime(int i)
    {
      if (i == 2) return true;
      if (i <= 1 || i % 2 == 0) return false;
      double sqrt_i = Math.Sqrt(i);
      for (int div = 3; div <= sqrt_i; div += 2)
      {
        if (i % div == 0) return false;
      }
      return true;
    }

    static void Foo3()
    {
      int n = 4;
      int next_N = 0;
      int last_N = 0;
      Task[] tasks = new Task[n];

      Console.WriteLine("Start");
      time.Start();
      for (int i = 0; i < tasks.Length; i++)
      {
        next_N += (int)(N / n);

        int[] args = new int[] { i, last_N, next_N };
        
        tasks[i] = Task.Factory.StartNew((arg) =>
        {
          int[] param = (int[])arg;
          Stopwatch t = new Stopwatch();
          t.Start();

          for (int i = param[1]; i < param[2]; i++)
          {
            //if (param[0] == 2)
            //  Console.WriteLine($"{param[0]}: {i}");
            isPrime(i);
          }

          t.Stop();
          Console.WriteLine($"Задача {param[0]} завершена за {time.Elapsed.ToString("mm\\:ss\\.ff")}");
        }, args);

        last_N = next_N;
      }

      Task.WaitAll(tasks);

      time.Stop();
      Console.WriteLine(time.Elapsed.ToString("mm\\:ss\\.ff"));
      Console.WriteLine("End");
    }
  }
}
