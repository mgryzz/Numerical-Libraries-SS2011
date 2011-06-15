#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

void read_matrix_from_file(double* matrix, std::string filename, int x_size,
		      int y_size, bool skip_header = true);
