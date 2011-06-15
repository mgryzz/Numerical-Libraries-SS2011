#include <iostream>
#include <nag.h>
#include <nag_stdlib.h>
#include <nagg02.h>
#include <time.h>

#define X(I, J) x[(I) * tdx + J]
#define CORR(I, J) corr[(I) * tdc + J]

using namespace std;

int main(void) {
  cout << "Starting Speedtest!" << endl;
  
  // Variables
  int iterations = 100;
  time_t starttime, runtime;
  tm *timestruct;

  // Running Benchmark
  starttime = time(0);

  for(int i=1; i<=iterations; i++){
    cout << "iteration " << i << endl;
    
    ///// INPUT /////

    Integer n = 10; // Anzahl Beobachtungen
    Integer m = 2;  // Anzahl Variablen
    double *x = NAG_ALLOC(n*m, double);  // Beobachtungsmatrix

    Integer tdx = m; // Stride seprating matrix elements???
    Integer *svar = (Integer *)0;
    Integer *sobs = (Integer *)0;
    Integer tdc = m; // tdx in corr???

    ///// Output ///// 
    double *corr = NAG_ALLOC(m*m, double); 
    NagError fail;
    INIT_FAIL(fail);
    
    //x = {1,2,2,4,3,6,4,8,5,10,6,12,7,14,8,16,9,18,10,20};

    X(0,0) = 1; X(0,1) = 2;
    X(1,0) = 1; X(1,1) = 2;
    X(2,0) = 1; X(2,1) = 2;
    X(3,0) = 1; X(3,1) = 2;
    X(4,0) = 1; X(4,1) = 2;
    X(5,0) = 1; X(5,1) = 2;
    X(6,0) = 1; X(6,1) = 2;
    X(7,0) = 1; X(7,1) = 2;
    X(8,0) = 1; X(8,1) = 2;
    X(9,0) = 1; X(9,1) = 2;


    nag_ken_spe_corr_coeff(n, m, x, tdx, svar, sobs, corr, tdc, &fail);

    cout << "correlation matrix:" << endl;

    for (int i = 0; i < m; i++){
      for (int j = 0; j < m; j++){
 	cout << "\t" << CORR(i,j);
      }
      cout << endl;
    }
  }
  
  runtime = time(0) - starttime;
  timestruct = localtime(&runtime);

	cout << "Runtime: " << runtime << endl;

  return(0);
}
