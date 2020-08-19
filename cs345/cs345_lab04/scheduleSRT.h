/***********************************************************************
* Component:
*    Scheduler SRT
* Author:
*    your name
* Summary: 
*    This is the base-class that enables various schedule algorithms
*    to simulate CPU Scheduling
************************************************************************/

#ifndef SCHEDULER_SRT
#define SCHEDULER_SRT
#include <vector>
#include "schedule.h"
#include <list>

/****************************************************
 * SRT
 * The Shortest Remaining Time Scheduler
 ***************************************************/
class SchedulerSRT : public Disbatcher
{
public:
   SchedulerSRT() : Disbatcher() {}

   // a new process has just been executed
/****************************************************
 * startProcess
 * Puts the process in the queue dependent on the time remaining
 ***************************************************/
   void startProcess(int pid)
   {
      std::list<int>::iterator it = readyQueue.begin(); // list iterators
      std::list<int>::iterator end = readyQueue.end();
      while(it != end && processes[*it].getTimeLeft() < processes[pid].getTimeLeft())
      {
         it++; // loop list until the process should be inserted
      }
      readyQueue.insert(it, pid); // insert into the place determined by the loop
   }
/****************************************************
 * clock
 * re-sorts depending on time remaining then runs the program
 * with the least time remaining.
 ***************************************************/
   bool clock()
   {
      if (pidCurrent == PID_NONE || processes[pidCurrent].isDone()) // is the process done
      {
         if (readyQueue.size() > 0) // make sure something is in the queue
         {
            pidCurrent = readyQueue.front(); // set the current process to the beginning of queue
            readyQueue.pop_front();
         }
         else
            pidCurrent = PID_NONE;
      }
      else if (processes[pidCurrent].getTimeLeft() > processes[readyQueue.front()].getTimeLeft())
      {
         std::list<int>::iterator it = readyQueue.begin(); // iterators
         std::list<int>::iterator end = readyQueue.end();
         while (it != end && processes[*it].getTimeLeft() < processes[pidCurrent].getTimeLeft())
         {
            it++; // loop for where to insert the process
         }
         readyQueue.insert(it, pidCurrent); // insert the process
         pidCurrent = readyQueue.front();
         readyQueue.pop_front();
      }
         
      return Disbatcher::clock();
   }

  private:
      std::list <int> readyQueue;
};

#endif // SCHEDULE_SRT
