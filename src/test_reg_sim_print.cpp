#include <iostream>
#include <nag.h>
#include <nag_stdlib.h>
#include <nagg02.h>
#include "Timer.h"
#include "utils.h"
#define X(I, J) x_read[(I) * x_size + J]

using namespace std;

int main(int argc, char* argv[]) {
  
  // Options
  int iterations = 100;
  int x_size = 3;
  int y_size = 10;
  int ip = 0; // Nicht benutzt
  bool read_matrix = false;
  bool ms_output = false, us_output = false;
  bool verbose = true;
  string filename = "";
  Timer timer;

  // Lese Kommandozeilen Argumente
  parse_arguments(argc, argv, &iterations, &read_matrix, &filename, &x_size, &y_size, &ip,
		  &ms_output, &us_output, &verbose);

  ///// INPUT /////
  Nag_SumSquare mean = Nag_AboutMean;	//
  double *x_read = NAG_ALLOC(y_size*x_size, double);
  double *x = NAG_ALLOC(y_size, double); //
  double *y = NAG_ALLOC(y_size, double); //
  double *wt = NULL;

  if(read_matrix){
    read_matrix_from_file(x_read, filename, x_size, y_size, true);
  }else{
    create_random_matrix(x_read, x_size, y_size);
  }

  // Werte aus eingelesener Beobachtungsmatrix in Vektoren kopieren
  for(int i=0; i<y_size; i++){
    y[i] = X(i, 0);
    x[i] = X(i, 2);
  }

  ///// Output ///// 
  double a, b, err_a, err_b, rsq, rss, df;
  NagError fail;
  INIT_FAIL(fail);

  // Running Benchmark
  timer.start();

  for(int i=1; i<=iterations; i++){
    nag_simple_linear_regression(mean, y_size, x, y, wt, &a, &b, &err_a, &err_b, &rsq, &rss, &df, &fail);
  }

  timer.stop();

  if(ms_output){
    cout << timer.getTimeString_ms() << endl;
  }else if(us_output){
    cout << timer.getTimeString_us() << endl;    
  }else{
    cout << timer.getTimeString() << endl;
  }

  // Gebe Speicher frei
  if(x_read) NAG_FREE(x_read);
  if(x) NAG_FREE(x);
  if(y) NAG_FREE(y);

  return(0);
}
