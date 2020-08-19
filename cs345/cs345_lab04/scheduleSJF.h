/***********************************************************************
* Component:
*    Scheduler SJF
* Author:
*    your name
* Summary: 
*    This is the base-class that enables various schedule algorithms
*    to simulate CPU Scheduling
************************************************************************/

#ifndef SCHEDULER_SJF
#define SCHEDULER_SJF

#include "schedule.h"
#include <vector>
#include <iostream>
#include <list>
/****************************************************
 * SJF
 * The Shortest Job First scheduler
 ***************************************************/
class SchedulerSJF : public Disbatcher
{
public:
   SchedulerSJF() : Disbatcher() {}


 /****************************************************
 * startProcess
 * adds new processes onto the queue based on the time they have left.
 ***************************************************/
   void startProcess(int pid)
   {
      std::list<int>::iterator it = readyQueue.begin();
      std::list<int>::iterator end = readyQueue.end();
      while(it != end && processes[*it].getTimeLeft() < processes[pid].getTimeLeft())
      {
         it++; // Finds where to put the new PID
      }
      readyQueue.insert(it, pid);
   }
/****************************************************
 * clock
 * Runs the first program on the queue
 ***************************************************/
   bool clock()
   {
      if (pidCurrent == PID_NONE || processes[pidCurrent].isDone())
      {
         if (readyQueue.size())
         {
            pidCurrent = readyQueue.front(); // run the program in front
                                             // when the process finishes
            readyQueue.pop_front();
         }
         else
            pidCurrent = PID_NONE;
      }
      return Disbatcher::clock();
   }


private:
   std::vector <int> sortedJobs;
   std::vector <int> jobVector;
      std::list <int> readyQueue;
};

#endif // SCHEDULE_SJF
