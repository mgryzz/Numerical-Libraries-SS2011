#include <iostream>
#include <nag.h>
#include <time.h>

using namespace std;

int main(void) {
  cout << "Starting Speedtest!" << endl;
  
  // Variables
  int iterations = 100;
  time_t starttime, runtime;
  tm *timestruct;

  // Running Benchmark
  starttime = time(0);

  for(int i=1; i<=iterations; i++){
    cout << "iteration " << i << endl;

    
  }
  
  runtime = time(0) - starttime;
  timestruct = localtime(&runtime);

	cout << "Runtime: " << runtime << endl;

  return(0);
}
