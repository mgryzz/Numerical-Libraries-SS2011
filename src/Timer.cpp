#include "Timer.h"

using namespace std;

Timer::Timer(){}

Timer::~Timer(){}

void Timer::start(){
  gettimeofday(&this->_start, 0);
}


void Timer::stop(){
  gettimeofday(&this->_end, 0);
  

  long add_sec = this->_end.tv_sec - _start.tv_sec;
  long add_usec = this->_end.tv_usec - _start.tv_usec;

  this->_time_usec += add_usec;
  this->_time_sec += add_sec;
  
  // �berlauf bei den Mikrosekunden?
  if(this->_time_usec > 1000000){
    this->_time_sec++;
    this->_time_usec = this->_time_usec % 1000000;
  }
}

void Timer::reset(){
  this->_time_sec = 0;
  this->_time_usec = 0;
}

string Timer::getTimeString(){
  ostringstream o;
  
  o << "Runtime (Sek.+Mikrosek.): " << this->_time_sec << "+" << 
    this->_time_usec;

  return o.str();
}
