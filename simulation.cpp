#include <string>
#include <fstream>
#include <iostream>
#include <queue> 
#include <vector>
#include <stdlib.h>
#include "Time.h"
#include "Jobs.h"

using namespace std;

void printStats(string type);

const int AVG_ARRIVAL_INTERVAL = 5, AVG_EXECUTION_DURATION = 15, TOTAL_JOBS = 50;
int exeMin = AVG_EXECUTION_DURATION, exeMax = 0, arrMin = AVG_ARRIVAL_INTERVAL, arrMax = 0, waitMin = 0, waitMax = 0, waitTotal = 0, noWaitCount = 0;

int main(int argc, char *argv[]) {
  ofstream fifo_out ("fifo.log"), sjf_out ("sjf.log");
  queue<Jobs> event1, event2, fifo;
  priority_queue<Jobs, vector<Jobs>, greater<Jobs> > sjf;
  srand(time(NULL));
  Time time;
 
  for (int i = 0; i < TOTAL_JOBS; i ++) {
    int length = (rand() % AVG_EXECUTION_DURATION + 1) + (rand() % AVG_EXECUTION_DURATION + 1);
    int arrival = rand() % AVG_ARRIVAL_INTERVAL + rand() % AVG_ARRIVAL_INTERVAL;   
    event1.push(Jobs(arrival + time.getSeconds(), length));
    time = time + arrival;
  
    if (arrival < arrMin) 
      arrMin = arrival;
    if (arrival > arrMax) 
      arrMax = arrival;
    if (length < exeMin) 
      exeMin = length;
    if (length > exeMax) 
      exeMax = length;
  }

  int waitTime;
  Time::clock = event1.front().arrival();
  while (!event1.empty() || !fifo.empty()) {
    if (fifo.empty() && event1.front().arrival() > Time::clock) Time::clock = event1.front().arrival();
    while (!event1.empty() && event1.front().arrival() < Time::clock + 1) {
      fifo.push(event1.front()); 
      fifo_out << Time::clock << " " << event1.front() << " entered the queue. Arrival time: " << event1.front().arrival() << endl;
      event2.push(event1.front());
      event1.pop();
    }
  
    fifo.front().execute();
    waitTime = fifo.front().waitTime();
    fifo_out <<  Time::clock << " " << fifo.front() << " begins execution, wait time " << waitTime <<  " seconds" << endl;
    waitTotal += waitTime;
    if (waitTime == 0) noWaitCount ++;
    if (waitTime < waitMin) waitMin = waitTime;
    if (waitTime > waitMax) waitMax = waitTime;
    
    Time::clock += fifo.front().length();
    fifo_out << Time::clock << " " << fifo.front() << " terminates" << endl;
    fifo.pop();
  }
  
  printStats("FIFO");
  waitMin = 0;
  waitMax = 0;
  waitTotal = 0;
  noWaitCount = 0;
  
  Time::clock = event2.front().arrival();
  while (!event2.empty() || !sjf.empty()) {
    if (sjf.empty() && event2.front().arrival() > Time::clock) Time::clock = event2.front().arrival();
    while (!event2.empty() && event2.front().arrival() < Time::clock + 1) {
      sjf.push(event2.front());
      sjf_out << Time::clock << " " << event2.front() << " entered the system" << endl;
      event2.pop();
    }
    
    Jobs temp = sjf.top();
    temp.execute();
    waitTime = temp.waitTime();
    sjf_out <<  Time::clock << " " << sjf.top() << " begins execution, wait time " << waitTime <<  " seconds" << endl;
    waitTotal += waitTime;
    if (waitTime == 0) noWaitCount ++;
    if (waitTime < waitMin) waitMin = waitTime;
    if (waitTime > waitMax) waitMax = waitTime;
    
    Time::clock += sjf.top().length();
    sjf_out << Time::clock << " " << sjf.top() << " terminates" << endl;
    sjf.pop();
  }
  
  printStats("SJF");
  fifo_out.close();
  sjf_out.close();
  return 0;
}

void printStats(string type) {
  cout << type << " simulation results:\n Time ended: " << Time::clock << "\n Minimum execution time: " << exeMin << " seconds\n Maxim\
um execution time: "
       << exeMax << " seconds\n Minimum arrival interval: " << arrMin << " seconds\n Maximum arrival interval: " << arrMax << " seconds\n \
Minimum waiting time: "
       << waitMin << " seconds\n Maximum wait time: " << waitMax << " seconds\n Average wait time: " << waitTotal / TOTAL_JOBS
       << " seconds\n Number of jobs executed immediately: " << noWaitCount << endl;
}
