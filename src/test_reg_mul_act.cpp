#include <iostream>
#include <fstream>
#include <nag.h>
#include <nag_stdlib.h>
#include <nagg02.h>

#include "Timer.h"
#include "utils.h"

#define X(I, J) x[(I) * x_size + J]

using namespace std;

int main(int argc, char* argv[]) {
  
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


  ///// Function variables /////
  // Input

  Nag_IncludeMean mean = Nag_MeanInclude; // Benutze konstanten Term 
  Integer m = x_size; // Anzahl unabhängiger Variablen im Datensatz
  Integer tdx = m;
  Integer tdq = ip+1;
  //Integer sx[] = {0,1,1,1,1,1,0,0,0,0,0,0,0};
  Integer sx[m];
  sx[0] = 0;
  for(int i=1; i<m; i++){
    if(i < ip-1)
      sx[i] = 1;
    else
      sx[i] = 0;
  }

  // Testausgabe
  if(verbose){
  cout << "sx: (";
  for(int i=0; i<x_size; i++){
    cout << sx[i] << ", ";
  }
  cout << ")" << endl;
  }

  double tol = 0.000001; // Toleranz fü Matrix Elemente (falls < tol, dann 0)

  double *x = NAG_ALLOC(y_size*tdx, double); // Beobachtungsmatrix
  double *x_new = NAG_ALLOC(y_size, double); // hinzuzufügender Wert
  double *y = NAG_ALLOC(y_size, double); // Werte für abhängige Variable
  double *wt = NULL;

  // Matrix einlesen
  if(read_matrix){
    read_matrix_from_file(x, filename, x_size, y_size, true);
  }else{
    create_random_matrix(x, x_size, y_size);
  }
  
  // Testausgabe
//   if(verbose){
//   cout << "Beobachtungsmatrix:" << endl;
//   for(int i=0; i<y_size; i++){
//     for(int j=0; j<x_size; j++){
//       cout << "\t" << X(i, j);
//     }
//     cout << endl;
//   }
//   }

  // Werte für abhängige Variable in y kopieren 
  for(int i=0; i<y_size; i++){
    y[i] = X(i,0);
  }

  // Werte für neue Variable in x_new kopieren
  for(int i=0; i<y_size; i++){
    x_new[i] = X(i,ip-1);
  }

  // Testausgabe
//   if(verbose){
//   cout << "Vektor y:" << endl;
//   for(int i=0; i<y_size; i++){
//     cout << "\t" << y[i] << endl;
//   }
//   }

  /// Output 
  double rss = 0, df = 0;
  double *b = NAG_ALLOC(ip, double); // Die Koeffizienten
  double *se = NAG_ALLOC(ip, double); // Die Standartfehler
  double *cov = NAG_ALLOC((ip*ip+ip)/2, double); // ???
  double *res = NAG_ALLOC(y_size, double); // Die Residuen
  double *h = NAG_ALLOC(y_size, double); // Leverages
  double *q = NAG_ALLOC(y_size*tdq, double); // orthogonale Matrix Q
  Nag_Boolean svd; // Wurde SVD benutzt?
  Integer rank; // Rang der unabhängigen Variablen
  double *p = NAG_ALLOC(ip*(ip+2), double); //Informationen über QR-Zerlegung und SVD
  double *com_ar = NAG_ALLOC(5*(ip-1)*ip, double);

  NagError fail, fail_add, fail_upd;
  INIT_FAIL(fail); INIT_FAIL(fail_add); INIT_FAIL(fail_upd);
  
  if(verbose){
    cout << "Starting Speedtest nag_regsn_mult_linear!" << endl;
    cout << "Iterationen: " << iterations << endl;
  }

  // Alte Werte berechnen
  nag_regsn_mult_linear(mean, y_size, x, tdx, m, sx, ip-1, y, wt, &rss, &df, b, se,
			cov, res, h, q, tdq, &svd, &rank, p, tol, com_ar, &fail);

  if(verbose){
    cout << "Zwischenergebnisse:" << endl
	 << "\t" << "Koeffizienten: (";
    for(int i = 0; i<ip-1; i++){
      cout << b[i] << ", ";
    }
    cout << ")" << endl;
  }

  ///// Running Benchmark /////
  timer.start();
  
  for(int i=1; i<=iterations; i++){
     
    nag_regsn_mult_linear_add_var(y_size, ip-1, q, tdq, p, wt, x_new, &rss, tol, &fail_add);

    nag_regsn_mult_linear_upd_model(y_size, ip, q, tdq, &rss, &df, b, se, cov, &svd, 
    				    &rank, p, tol, &fail_upd);
  }

  timer.stop();

  if(fail.code != NE_NOERROR || fail_add.code != NE_NOERROR || fail_upd.code != NE_NOERROR ){
    cout << "Wärend der Regression ist ein Fehler aufgetreten: " 
	 << fail.message << fail_add.message << fail_upd.message << endl;
  }
 
  if(verbose){
    cout << "Ergebnisse:" << endl
	 << "\t" << "Koeffizienten: (";
    for(int i = 0; i<ip ; i++){
      cout << b[i] << ", ";
    }
    cout << ")" << endl;
  }
  

  if(ms_output){
    cout << timer.getTimeString_ms() << endl;
  }else if(us_output){
    cout << timer.getTimeString_us() << endl;    
  }else{
    cout << timer.getTimeString() << endl;
  }

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

  return(0);
}
