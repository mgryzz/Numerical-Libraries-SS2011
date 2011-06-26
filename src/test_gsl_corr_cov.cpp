// fertige header einbinden
#include <iostream>
#include <gsl/gsl_statistics_double.h>

// eigene header einbinden
#include "Timer.h"
#include "utils.h"

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
	int size_m = 3;
	int size_n = 10;
	bool output_ms = false;
	bool output_us = false;
	bool verbose = true;
	
	// kommandozeile parsen
	parse_arguments(argc, argv, &iterations, &read_file, &file_name, &size_m, &size_n, &output_ms, &output_us, &verbose);
	
	// eingabe
	double data1[size_n]; // beobachtungen merkmal 1
	size_t stride1 = 1; // schrittweite merkmal 1
	double data2[size_n]; // beobachtungen merkmal 2
	size_t stride2; // schrittweite merkmal 2
	size_t n = size_n; // anzahl beobachtungen
		
	// beoachtungsmatrix erstellen
	if(read_file) {
		read_matrix_from_file(x, file_name, size_m, size_n, true);
	} else {
		create_random_matrix(x, size_m, size_n);
	}
	
	// leistungstest starten
	cout << "Starte Leistungstest f�r nag_corr_cov()..." << endl;
	cout << "Iterationen: " << iterations << endl;
	
	// timer starten
	timer.start();
	
	// funktion aufrufen
	for(int i = 1; i <= iterations; i++) {
		correlation = gsl_stats_correlation(data1, stride1, data2, stride2, n);
	}
	
	// timer stoppen
	timer.stop();
	
	// korrelation ausgeben
	if(verbose) {
		cout << "Korrelation: " << correlation << endl;
	}
	
	// gemessene zeit ausgeben
	cout << timer.getTimeString() << endl;
	
	return(0);
	
}
