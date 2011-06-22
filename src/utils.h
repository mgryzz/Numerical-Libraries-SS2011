#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdlib.h>

/**
 * Diese Methode liest eine Matrix aus einer Datei ein.
 * Es wir dabei davon ausgegangen, dass die einzelnen Werte durch Tabs 
 * getrennt sind.
 * Der benötigte Speicher in matrix muss zuvor allokiert worden sein!
 */
void read_matrix_from_file(double* matrix, const std::string &filename, int x_size,
		      int y_size, bool skip_header = true);

/**
 * Erstellt eine Matrix, die mit Zufallszahlen gefüllt ist.
 * 
 * Der benötigte Speicher in matrix muss zuvor allokiert worden sein!
 */ 
void create_random_matrix(double* matrix, int x_size, int y_size, 
			  double min_value=0.0, double max_value=1000.0);


/**
 * Konvertiert einen String in eine double Zahl.
 */
double string_to_double( const std::string& s );

/**
 * Liest die Kommandozeilenparameter ein und speichert die Werte in den übergebenen Variablen.
 * 
 * Falls ein Parameter nicht angegeben wurde, wird der Wert der Variablen nicht geändert,
 * daher sollten alle Variablen mit Standartwerten initialisiert werden.
 */ 
void parse_arguments(int argc, char* argv[], int *iterations, bool *read_matrix, char *filename,
		     int *xs, int *ys);
