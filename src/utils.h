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


double string_to_double( const std::string& s );
