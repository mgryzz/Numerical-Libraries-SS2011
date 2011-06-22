
#include <iostream>
#include <gsl/gsl_fit.h>

#include "Timer.h"
#include "utils.h"

using namespace std;

int main (int argc, char* argv[])
{
  for(int i=0; i<argc; i++){
    cout << argv[i] << endl;
  }

  // Variables
  int iterations = 100;
  int x_size = 2;
  int y_size = 10;
  bool read_matrix = false;
  char *filename = "";
  Timer timer;

  parse_arguments(argc, argv, &iterations, &read_matrix, &filename);
  
  cout << "Starting Speedtest of gsl_fit_linear!" << endl;

  // Running Benchmark
  timer.start();

  for(int i=1; i<=iterations; i++){
    //cout << "iteration " << i << endl;
    
    ///// INPUT /////
    double x[10] = {0,1,2,3,4,5,6,7,8,9};
    double y[10];

    size_t n = 10;
    size_t xstride = 0;
    size_t ystride = 0;

    ///// OUTPUT /////
    double c0, c1;
    double cov00, cov01, cov11;
    double sumsq;
    
    double ret = gsl_fit_linear(x, xstride, y, ystride, n, &c0, &c1, &cov00, &cov01, 
				&cov11, &sumsq);
  }

  timer.stop();
    
  cout << timer.getTimeString() << endl;

  return(0);

}
