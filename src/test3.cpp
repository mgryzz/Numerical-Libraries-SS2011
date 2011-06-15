#include <iostream>
#include <nag.h>
#include <nag_stdlib.h>
#include <nagg02.h>
#include <time.h>
#include <sys/time.h>

#define X(I, J) x[(I) * tdx + J]
#define CORR(I, J) corr[(I) * tdc + J]

using namespace std;

int main(void) {
  cout << "Starting Speedtest!" << endl;
  
  // Variables
  int iterations = 100;
  timeval start, end;
  long runtime_sec, runtime_usec;

  // Running Benchmark
  gettimeofday(&start, 0);

  for(int i=1; i<=iterations; i++){
    cout << "iteration " << i << endl;
    
    ///// INPUT /////

    Nag_SumSquare mean = Nag_AboutMean;	//
    Integer n = 10; // Anzahl Beobachtungen
    double *x = NAG_ALLOC(n, double); //
    double *y = NAG_ALLOC(n, double); //
    double *wt = NAG_ALLOC(n, double); //

    ///// Output ///// 
    double a, b, err_a, err_b, rsq, rss, df;
    NagError fail;
    INIT_FAIL(fail);
    
    nag_simple_linear_regression(mean, n, x, y, wt, &a, &b, &err_a, &err_b, &rsq, &rss, &df, &fail);

  }

  gettimeofday(&end, 0);
  runtime_sec = end.tv_sec - start.tv_sec;
  runtime_usec = end.tv_usec - start.tv_usec;
  
  cout << "Runtime (Sek.+Mikrosek.): " << runtime_sec << "+" << runtime_usec << endl;

  return(0);
}
