
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
  string filename = "";
  Timer timer;

  // Lese Kommandozeilen Argumente
  parse_arguments(argc, argv, &iterations, &read_matrix, &filename, &x_size, &y_size);
  
  ///// INPUT /////
  double x_read[x_size][y_size];
  double x[y_size];
  double y[y_size];

  size_t n = 10;
  size_t xstride = 0;
  size_t ystride = 0;

  if(read_matrix){
    read_matrix_from_file(x_read, filename, x_size, y_size, true);
  }else{
    create_random_matrix(x_read, x_size, y_size);
  }

  // Werte aus eingelesener Beobachtungsmatrix in Vektoren kopieren
  for(int i=0; i<y_size; i++){
    y[i] = x_read[0][i];
    x[i] = x_read[1][i];
  }

  ///// OUTPUT /////
  double c0, c1;
  double cov00, cov01, cov11;
  double sumsq;

  cout << "Starting Speedtest of gsl_fit_linear!" << endl;

  // Running Benchmark
  timer.start();

  for(int i=1; i<=iterations; i++){
    //cout << "iteration " << i << endl;
    
    
    
    double ret = gsl_fit_linear(x, xstride, y, ystride, n, &c0, &c1, &cov00, &cov01, 
				&cov11, &sumsq);
  }

  timer.stop();
    
  cout << timer.getTimeString() << endl;

  return(0);

}
