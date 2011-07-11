// fertige header einbinden
#include <iostream>
#include <nag.h>
#include <nag_stdlib.h>
#include <nagg02.h>

// eigene header einbinden
#include "Timer.h"
#include "utils.h"

// makros definieren
#define X(I, J) x[(I) * tdx + J]
#define R(I, J) r[(I) * tdr + J]
#define V(I, J) v[(I) * tdv + J]

// namespace festlegen
using namespace std;

/*
* funktion main
*/
int main(int argc, char* argv[]) {
	
	// variablen deklarieren
	// eigene
	Timer timer;
	int iterations = 100;
	bool read_file = false;
	string file_name = "";
	int size_m = 2;
	int size_n = 10;
	bool output_ms = false;
	bool output_us = false;
	bool verbose = true;
	
	// kommandozeile parsen
	parse_arguments(argc, argv, &iterations, &read_file, &file_name, &size_m, &size_n, &output_ms, &output_us, &verbose);
	
	// eingabe
	Integer n = size_n; // anzahl beobachtungen
	Integer m = size_m;  // anzahl merkmale
	Integer tdx = m; // schrittweite beobachtungsmatrix
	double *x = NAG_ALLOC(n * tdx, double);  // beobachtungsmatrix
	Integer *sx = (Integer *)0; // einbezug merkmale
	double *wt = (double *)0; // gewichtung beobachtungen
	Integer tdr = m; // schrittweite korrelationsmatrix
	Integer tdv = m; // schrittweite kovarianzmatrix
	
	// ausgabe
	double sw; // summe gewichte
	double *wmean = NAG_ALLOC(m, double); // erwartungswerte
	double *std = NAG_ALLOC(m, double); // standardabweichungen
	double *r = NAG_ALLOC(m * tdr, double); // korrelationsmatrix
	double *v = NAG_ALLOC(m * tdv, double); // kovarianzmatrix
	NagError fail; // fehler
	INIT_FAIL(fail);
	
	// beoachtungsmatrix erstellen
	if(read_file) {
		read_matrix_from_file(x, file_name, size_m, size_n, true);
	} else {
		create_random_matrix(x, size_m, size_n);
	}
	
	// timer starten
	timer.start();
	
	// funktion aufrufen
	for(int i = 1; i <= iterations; i++) {
		nag_corr_cov(n, m, x, tdx, sx, wt, &sw, wmean, std, r, tdr, v, tdv, &fail);
	}
	
	// timer stoppen
	timer.stop();
	
	// gemessene zeit ausgeben
	if(output_ms) {
		cout << timer.getTimeString_ms() << endl;
	} else if(output_us) {
		cout << timer.getTimeString_us() << endl;    
	} else {
		cout << timer.getTimeString() << endl;
	}
	
	return(0);
	
}
