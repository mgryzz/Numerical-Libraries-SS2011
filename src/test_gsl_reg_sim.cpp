#include <iostream>
#include <gsl/gsl_fit.h>

#include "Timer.h"
#include "utils.h"

using namespace std;

int main (int argc, char* argv[])
{

  // Options
  int iterations = 100;
  int x_size = 2;
  int y_size = 10;
  bool read_matrix = false;
  bool ms_output = false, us_output = false;
  bool verbose = true;
  string filename = "";
  Timer timer;

  // Lese Kommandozeilen Argumente
  parse_arguments(argc, argv, &iterations, &read_matrix, &filename, &x_size, &y_size,
		  &ms_output, &us_output, &verbose);
  
  ///// INPUT /////
  double x_read[y_size][x_size];
  double x[y_size];
  double y[y_size];

  size_t n = 10;
  size_t xstride = 0;
  size_t ystride = 0;

  if(read_matrix){
    read_matrix_from_file((double*) x_read, filename, x_size, y_size, true);
  }else{
    create_random_matrix((double *) x_read, x_size, y_size);
  }
  
  // Testausgabe
  if(verbose){
  cout << "Beobachtungsmatrix:" << endl;
  for(int i=0; i<y_size; i++){
    for(int j=0; j<x_size; j++){
      cout << "\t" << x_read[j][i];
    }
    cout << endl;
  }
  }

  // Werte aus eingelesener Beobachtungsmatrix in Vektoren kopieren
  for(int i=0; i<y_size; i++){
    y[i] = x_read[i][0];
    x[i] = x_read[i][1];
  }

  // Testausgabe
  if(verbose){
  cout << "Vektor x:" << endl;
  for(int i=0; i<y_size; i++){
    cout << "\t" << x[i] << endl;
  }

  cout << "Vektor y:" << endl;
  for(int i=0; i<y_size; i++){
    cout << "\t" << y[i] << endl;
  }
  }

  ///// OUTPUT /////
  double c0, c1;
  double cov00, cov01, cov11;
  double sumsq;

  if(verbose){
  cout << "Starting Speedtest of gsl_fit_linear!" << endl;
  cout << "Iterationen: " << iterations << endl;
  }

  // Running Benchmark
  timer.start();

  for(int i=1; i<=iterations; i++){    
    
    double ret = gsl_fit_linear(x, xstride, y, ystride, n, &c0, &c1, &cov00, &cov01, 
				&cov11, &sumsq);
  }
  
  timer.stop();

  if(verbose){
    cout << "Ergebnisse: " << endl
	 << "\t" << "alpha: " << c0 << endl
	 << "\t" << "beta: " << c1 << endl
	 << "\t" << "cov00: " << cov00 << endl
	 << "\t" << "cov01: " << cov01 << endl
	 << "\t" << "cov11: " << cov11 << endl
	 << "\t" << "Fehlerquadratsumme: " << sumsq << endl;
  }
    
  if(ms_output){
    cout << timer.getTimeString_ms() << endl;
  }else if(us_output){
    cout << timer.getTimeString_us() << endl;    
  }else{
    cout << timer.getTimeString() << endl;
  }

  return(0);

}
