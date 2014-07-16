#ifndef JOBS_H
#define JOBS_H

#include <iostream>
#include "Time.h"

class Jobs {
  friend bool operator <(const Jobs &j1, const Jobs &j2);
  friend bool operator >(const Jobs &j1, const Jobs &j2);
  friend std::ostream &operator <<(std::ostream &os, const Jobs &jobs);
 public:
  Jobs (int arrival, int length) : tArrival(Time(arrival)) , tLength(Time(length)), id(idCount++) {}
  Jobs (const Jobs &other) :  id(other.id), tArrival(other.tArrival), tLength(other.tLength), execution(other.execution) {}
  Time arrival() const {return tArrival;}
  Time length() const {return tLength;}
  void execute() {execution = Time::clock;}
  int waitTime() {return execution.getSeconds() - tArrival.getSeconds();}
 private:
  static int idCount ;
  int id;
  Time tArrival, tLength, execution;
};

int Jobs::idCount = 1;
bool operator <(const Jobs &j1, const Jobs &j2) {return j1.tLength < j2.tLength;}
bool operator >(const Jobs &j1, const Jobs &j2) {return j1.tLength > j2.tLength;}
std::ostream &operator <<(std::ostream &os, const Jobs &jobs) {
  os << "Job #" << jobs.id << ", (Execution Time: " << jobs.tLength.getSeconds() << " seconds)";
  return os;
}

#endif
