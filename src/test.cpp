#include <iostream>
#include <nag.h>
#include <nag_stdlib.h>
#include <nagg02.h>
#include <time.h>

#include "utils.h"

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
    Integer m = 10;  // Anzahl Variablen
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

//     X(0,0) = 1; X(0,1) = 2;
//     X(1,0) = 2; X(1,1) = 4;
//     X(2,0) = 3; X(2,1) = 6;
//     X(3,0) = 4; X(3,1) = 8;
//     X(4,0) = 5; X(4,1) = 10;
//     X(5,0) = 6; X(5,1) = 12;
//     X(6,0) = 7; X(6,1) = 14;
//     X(7,0) = 8; X(7,1) = 16;
//     X(8,0) = 9; X(8,1) = 18;
//     X(9,0) = 10; X(9,1) = 20;

    read_matrix_from_file(x, "data/miete03.asc", 10, 10);

    for (int i = 0; i < n; i++){
      for (int j = 0; j < m; j++){
 	cout << "\t" << X(i,j);
      }
      cout << endl;
    }

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
