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

      M(linecount, cellcount) = string_to_double(cell);
      cout << "\t" << cell << "(" << M(cellcount, linecount) << ")";
      cellcount++;
    }

    // Ignoriere alle restlichen Daten in dieser Zeile
    //data.ignore(numeric_limits<std::streamsize>::max(), '\n');
    
    cout << endl;

    linecount++;
  }
  
  // Schließe Datenstream
  data.close();
}

void create_random_matrix(double* matrix, int x_size, int y_size, 
			  double min_value, double max_value){
  
  // Initialisiere seed
  srand((unsigned)time(0)); 

  for(int i=0; i < y_size; i++){
    for(int j=0; j < x_size; j++){
      // Erzeuge Zufallsnummer
      double random = min_value + ((double)rand() / RAND_MAX) * 
	(max_value - min_value);

      M(i,j) = random;
    }
  }
}


double string_to_double( const string& s )
{
  std::istringstream i(s);
  double x;
  if (!(i >> x))
    return 0;
  return x;
} 
