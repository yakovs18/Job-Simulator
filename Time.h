#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <iomanip>      
class Time {
  friend bool operator >(const Time &t1, const Time &t2);
  friend bool operator <(const Time &t1, const Time &t2);
  friend Time operator +(const Time &t1, const Time &t2);
  friend Time operator +(const Time &t1, const int i);
  friend Time operator -(const Time &t1, const Time &t2);
  friend std::ostream &operator <<(std::ostream &os, const Time &time);
 public:
  Time(int seconds = 0) : seconds(seconds) {}
  Time &operator =(const Time &other) {seconds = other.seconds; return *this;}
  Time &operator +=(const Time &other) {seconds += other.seconds; return *this;}
  int getSeconds() const {return seconds;}
  static Time clock;
 private:
  int seconds;
};

Time Time::clock;
bool operator <(const Time &t1, const Time &t2) {return t1.seconds < t2.seconds;}
bool operator >(const Time &t1, const Time &t2) {return t1.seconds > t2.seconds;}
Time operator +(const Time &t1, const Time &t2) {return Time(t1.seconds + t2.seconds);}
Time operator +(const Time &t1, const int i) {return Time(t1.seconds + i);}
Time operator -(const Time &t1, const Time &t2) {return Time(t1.seconds - t2.seconds);}
std::ostream &operator <<(std::ostream &os, const Time &time) {
  os << std::setfill ('0') << std::setw (2) << time.seconds / 3600 << ":" << std::setw (2) << time.seconds / 60 % 60 << ":" << \
    std::setw (2) << time.seconds % 60;
  return os;
}

#endif
