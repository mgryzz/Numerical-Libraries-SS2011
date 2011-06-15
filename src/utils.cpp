#include "utils.h"

#define M(I, J) matrix[(I) * x_size + J]

using namespace std;

void read_matrix_from_file(double *matrix, const string &filename, int x_size,
		      int y_size, bool skip_header){
  
 
  ifstream data;
  string line;

  // Öffne Datenstream
  data.open(strdup(filename.c_str()), ifstream::in);

  if(skip_header){
    getline(data, line);
  }

  int linecount = 0;
  while(getline(data, line) && linecount < y_size){
    
    stringstream lineStream(line);
    string cell;
    int cellcount = 0;
    
 

    while(getline(lineStream, cell, '\t') && cellcount < x_size){

      M(cellcount, linecount) = string_to_double(cell);
      cout << "\t" << cell << "(" << M(cellcount, linecount) << ")";
    }
    
    cout << endl;

    linecount++;
  }
  
  // Schließe Datenstream
  data.close();
}


double string_to_double( const string& s )
{
  std::istringstream i(s);
  double x;
  if (!(i >> x))
    return 0;
  return x;
} 
