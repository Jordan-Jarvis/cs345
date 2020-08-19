/***********************************************************************
* Component:
*    Scheduler FCFS
* Author:
*    your name
* Summary: 
*    This is the base-class that enables various schedule algorithms
*    to simulate CPU Scheduling
************************************************************************/

#ifndef SCHEDULER_FCFS
#define SCHEDULER_FCFS

#include <queue>      // for the ready queue
#include <cassert>    // because I am paranoid
#include "schedule.h"

#include <iostream>
using namespace std;

/****************************************************
 * FCFS
 * The first-come, first-serve scheduler
 ***************************************************/
class SchedulerFCFS : public Disbatcher
{
public:
   SchedulerFCFS() : Disbatcher() {}

   // a new process has just been executed. Here we will put it on the
   // back of the ready queue
   void startProcess(int pid)
   {
      readyQueue.push(pid);
   }
      
   // execute one clock cycle. Here we will determine whether we need
   // to switch to a new process
   bool clock()
   {
      // is the current process finished or is there no process selected?
      if (pidCurrent == PID_NONE ||
          processes[pidCurrent].isDone())
      {
         // if there is something on the ready queue, then take the front
         // element. When we do this, we remove the item from the ready queue
         // and place it in pidCurrent.
         if (readyQueue.size())
         {
            pidCurrent = readyQueue.front();
            readyQueue.pop();
            assert(pidCurrent >= 0 && pidCurrent <= processes.size());
         }
         // if there is nothing in the ready queue, then set pidCurrent
         // to none. This means nothing is currently executing in the queue
         else
            pidCurrent = PID_NONE;
      }

      // call the base-class which will handle a variety of housekeeping chores
      return Disbatcher::clock();
   }

private:
   // this will represent the queue of processes which are awaiting
   // execution. We will use a queue because it enforces FCFS order.
   // The data-type is an INT because we are just storing a PID
   std::queue <int> readyQueue;
};

#endif // SCHEDULE_FCFS
