#include <string>
#include <sstream>
#include <sys/time.h>
#include <iostream>
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

  /**
   * Gibt einen lesbaren String mit der Laufzeit aus.
   * 
   * Für die Ausgabe auf der Konsole
   */
  std::string getTimeString();
  
  /**
   * Gibt die Laufzeit als einfache Zahl in Mikro- oder Millisekunden aus.
   *
   * Für die Ausgabe in eine Datei.
   */
  std::string getTimeString_ms();
  std::string getTimeString_us();
};
