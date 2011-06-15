#include <string>
#include <sstream>
#include <sys/time.h>
//#include <time.h>

class Timer{
 private:
  long _time_sec, _time_usec;
  timeval _start, _end;

 public:
  Timer();
  virtual ~Timer();

  void start();
  void stop();
  void reset();

  std::string getTimeString();
};
