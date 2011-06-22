#include <iostream>
#include <fstream>
#include <nag.h>
#include <nag_stdlib.h>
#include <nagg02.h>

#include "Timer.h"
#include "utils.h"

#define X(I, J) x[(I) * tdx + J]

using namespace std;

int main(void) {
  cout << "Starting Speedtest nag_regsn_mult_linear!" << endl;
  ///// Benchmark Variables /////
  int iterations = 1000;
  Timer timer;
  
  ///// Function variables /////
  // Input

  Nag_IncludeMean mean = Nag_MeanInclude; // Benutze konstanten Term 
  Integer n = 2053; // Anzahl Beobachtungen
  Integer m = 13; // Anzahl unabhängiger Variablen im Datensatz
  Integer tdx = m;
  Integer ip = 6; // Anzahl unabhängiger Variablen im Modell
  Integer tdq = ip+1;
  Integer sx[] = {0,1,1,1,1,1,0,0,0,0,0,0,0};
  double tol = 0.000001; // Toleranz fü Matrix Elemente (falls < tol, dann 0)

  double *x = NAG_ALLOC(n*tdx, double); // Beobachtungsmatrix
  double *y = NAG_ALLOC(n, double); // Werte für abhängige Variable
  //double *wt = NAG_ALLOC(n, double); // Gewichtungen
  double *wt = NULL;

  // Matrix einlesen
  read_matrix_from_file(x, "data/miete03.asc", 13, 2053);

  /*fstream file;
  file.open("data/x-out.txt", ios::out|ios::trunc);

  for (int i = 0; i < n; i++){
    for (int j = 0; j < m; j++){
      file << "\t" << X(i,j);
    }
    file << endl;
   }
  
  file.close();
  */

  // Werte für abhängige Variable in y kopieren 
  for(int i=0; i<n; i++){
    y[i] = X(i,0);
  }

  // test output
  /*
  file.open("data/y-out.txt", ios::out|ios::trunc);

  file << "y: " << endl;
  for(int i=0; i<n; i++){
    file << y[i] << endl;
  }

  file.close();
  */

  /// Output 
  double rss = 0, df = 0;
  double *b = NAG_ALLOC(ip, double); // Die Koeffizienten
  double *se = NAG_ALLOC(ip, double); // Die Standartfehler
  double *cov = NAG_ALLOC((ip*ip+ip)/2, double); // ???
  double *res = NAG_ALLOC(n, double); // Die Residuen
  double *h = NAG_ALLOC(n, double); // Leverages
  double *q = NAG_ALLOC(n*tdq, double); // orthogonale Matrix Q
  Nag_Boolean svd; // Wurde SVD benutzt?
  Integer rank; // Rang der unabhängigen Variablen
  double *p = NAG_ALLOC(ip*(ip+2), double); //Informationen über QR-Zerlegung und SVD
  double *com_ar = NAG_ALLOC(5*(ip-1)*ip, double);

  NagError fail;
  INIT_FAIL(fail);
  

  ///// Running Benchmark /////
  timer.start();
  
  for(int i=1; i<=iterations; i++){
    //cout << "iteration " << i << endl;   
    
    // Funktionsaufruf
    nag_regsn_mult_linear(mean, n, x, tdx, m, sx, ip, y, wt, &rss, &df, b, se,
			  cov, res, h, q, tdq, &svd, &rank, p, tol, com_ar, &fail);
  }

  timer.stop();

  if(fail.code != NE_NOERROR){
    cout << "Wärend der Regression ist ein Fehler aufgetreten: " 
	 << fail.message << endl;
  }
  
  cout << "Anzahl Freiheitsgrade: " << df << endl;
    
  // Gebe Speicher frei
  if(x) NAG_FREE(x);
  if(y) NAG_FREE(y);
  if(wt) NAG_FREE(wt);
  if(b) NAG_FREE(b);
  if(se) NAG_FREE(se);
  if(cov) NAG_FREE(cov);
  if(res) NAG_FREE(res);
  if(h) NAG_FREE(h);
  if(q) NAG_FREE(q);
  if(p) NAG_FREE(p);
  if(com_ar) NAG_FREE(com_ar);

  // Gebe Laufzeitinformationen aus:
  cout << timer.getTimeString() << endl;

  return(0);
}
