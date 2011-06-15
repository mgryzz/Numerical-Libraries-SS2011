#include <iostream>
#include <nag.h>
#include <nag_stdlib.h>
#include <nagg02.h>
#include <time.h>
#include <sys/time.h>

#define X(I, J) x[(I) * tdx + J]
#define R(I, J) r[(I) * tdr + J]
#define V(I, J) v[(I) * tdv + J]

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

    Integer n = 10; // Anzahl Beobachtungen
    Integer m = 2;  // Anzahl Variablen
    Integer tdx = m; // Schrittweite Beobachtungsmatrix
    double *x = NAG_ALLOC(n*tdx, double);  // Beobachtungsmatrix

    Integer *sx = (Integer *)0; // Einbezug Variablen
    double *wt = (double *)0; // Gewichtung Beobachtungen
    Integer tdr = m; // Schrittweite Korrelationsmatrix???
    Integer tdv = m; // Schrittweite Kovarianzmatrix??? 

    ///// Output ///// 
    double sw; // Summe der Gewichte
    double *wmean = NAG_ALLOC(m, double); // Erwartungswerte
    double *std = NAG_ALLOC(m, double); // Standardabweichungen
    double *r = NAG_ALLOC(n*tdr, double); // Korrelationsmatrix
    double *v = NAG_ALLOC(m*tdv, double); // Kovarianzmatrix
    NagError fail;
    INIT_FAIL(fail);
    
    //x = {1,2,2,4,3,6,4,8,5,10,6,12,7,14,8,16,9,18,10,20};

    X(0,0) = 1; X(0,1) = 3;
    X(1,0) = 2; X(1,1) = 4;
    X(2,0) = 3; X(2,1) = 6;
    X(3,0) = 4; X(3,1) = 9;
    X(4,0) = 5; X(4,1) = 10;
    X(5,0) = 6; X(5,1) = 11;
    X(6,0) = 7; X(6,1) = 14;
    X(7,0) = 8; X(7,1) = 17;
    X(8,0) = 9; X(8,1) = 18;
    X(9,0) = 10; X(9,1) = 19;

    nag_corr_cov(n, m, x, tdx, sx, wt, &sw, wmean, std, r, tdr, v, tdv, &fail);
    cout << "correlation matrix:" << endl;

    for (int i = 0; i < m; i++){
      for (int j = 0; j < m; j++){
 	cout << "\t" << R(i,j);
      }
      cout << endl;
    }
  }
  
  gettimeofday(&end, 0);
  runtime_sec = end.tv_sec - start.tv_sec;
  runtime_usec = end.tv_usec - start.tv_usec;
  
  cout << "Runtime (Sek.+Mikrosek.): " << runtime_sec << "+" << runtime_usec << endl;

  return(0);
}
