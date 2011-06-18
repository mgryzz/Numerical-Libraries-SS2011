#include <iostream>
#include <nag.h>
#include <nag_stdlib.h>
#include <nagg02.h>

#include "Timer.h"
#include "utils.h"

#define X(I, J) x[(I) * tdx + J]

using namespace std;

int main(void) {
  cout << "Starting Speedtest of nag_simple_linear_regression!" << endl;
  
  // Variables
  int iterations = 100;
  Timer timer;

  // Running Benchmark
  timer.start();

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

  timer.stop();
    
  cout << timer.getTimeString() << endl;

  return(0);
}
