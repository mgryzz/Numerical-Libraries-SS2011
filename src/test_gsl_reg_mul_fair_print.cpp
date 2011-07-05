#include <iostream>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_multifit.h>
#include <gsl/gsl_statistics_double.h>
#include <math.h>
#include "Timer.h"
#include "utils.h"

using namespace std;

int main (int argc, char* argv[])
{
  // Options
  int iterations = 100;
  int x_size = 3;
  int y_size = 10;
  int ip = 3;
  bool read_matrix = false;
  bool ms_output = false, us_output = false;
  bool verbose = true;
  string filename = "";
  Timer timer;

  // Lese Kommandozeilen Argumente
  parse_arguments(argc, argv, &iterations, &read_matrix, &filename, &x_size, &y_size, &ip,
		  &ms_output, &us_output, &verbose);
  
  ///// INPUT /////
  double x_read[y_size][x_size];
  gsl_matrix *x = gsl_matrix_alloc(y_size, ip);
  gsl_vector *y = gsl_vector_alloc(y_size);
  double w[y_size];

  if(read_matrix){
    read_matrix_from_file((double*) x_read, filename, x_size, y_size, true);
  }else{
    create_random_matrix((double *) x_read, x_size, y_size);
  }

  // Werte in x und y kopieren
  for(int i=0; i<y_size; i++){
    gsl_matrix_set(x, i, 0, 1);
  }
  for(int i=0; i<y_size; i++){
    for(int j=1; j<ip; j++){
      gsl_matrix_set(x, i, j, x_read[i][j]);
    }
  }
  
  for(int i=0; i<y_size; i++){
    gsl_vector_set(y, i, x_read[i][0]);
  }

  ///// OUTPUT /////
  gsl_vector *c = gsl_vector_alloc(ip);
  gsl_matrix *cov = gsl_matrix_alloc(ip, ip);
  double chisq; // residual sum of squares
  gsl_vector *r = gsl_vector_alloc(y_size);
  gsl_vector *se = gsl_vector_alloc(ip);

  // Workspace erstellen
  gsl_multifit_linear_workspace *wspace = gsl_multifit_linear_alloc(y_size, ip);
  
  // Running Benchmark
  timer.start();

  double ret;
  for(int i=1; i<=iterations; i++){    
    
    ret = gsl_multifit_linear(x, y, c, cov, &chisq, wspace);
    
    // Standartfehler berechnen
    for(int i=0; i<ip; i++){
      gsl_vector_set(se, i, sqrt(gsl_matrix_get(cov, i, i)));
    }

    // Residuen berechnen
    gsl_multifit_linear_residuals(x, y, c, r);
  }
  
  timer.stop();

  if(ms_output){
    cout << timer.getTimeString_ms() << endl;
  }else if(us_output){
    cout << timer.getTimeString_us() << endl;    
  }else{
    cout << timer.getTimeString() << endl;
  }

  // Speicher freigeben
  gsl_multifit_linear_free(wspace);
  gsl_matrix_free(x);
  gsl_matrix_free(cov);
  gsl_vector_free(y);
  gsl_vector_free(c);
  gsl_vector_free(r);

  return(0);
}
