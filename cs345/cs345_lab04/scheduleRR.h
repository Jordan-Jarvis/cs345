/***********************************************************************
* Component:
*    Scheduler RR
* Author:
*    your name
* Summary: 
*    This is the base-class that enables various schedule algorithms
*    to simulate CPU Scheduling
************************************************************************/

#ifndef SCHEDULER_RR
#define SCHEDULER_RR

#include <cassert>    // because I am paranoid
#include "schedule.h"
#include <queue>    // for the ready queue

#include <iostream>
using namespace std;

/****************************************************
 * RR
 * The Round Robin scheduler
 ***************************************************/
class SchedulerRR : public Disbatcher
{
public:
   SchedulerRR(int q) : Disbatcher(),
      timeQuantaDuration(q) {timeRun = 0;}
/****************************************************
 * startProcess
 * puts a process on the back of the queue
 ***************************************************/
   void startProcess(int pid)
   { 
   //put it on the queue
      readyQueue.push(pid);
   }
      
   // execute one clock cycle
/****************************************************
* clock
* runs the program until the time is up then switches
* it to the next program in the queue
***************************************************/
   bool clock()
   {
      
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
         {
            pidCurrent = PID_NONE;
         }
         // set the time run to 1 because the process is running
         timeRun = 1;
      }
      else
      {
         if (timeRun == timeQuantaDuration) // has the program been using the cpu long enough?
         {
            readyQueue.push(pidCurrent); //push the current process onto the back of the queue
            pidCurrent = readyQueue.front(); // push the first item on the queue
            readyQueue.pop(); // pop the item that is now current
            assert(pidCurrent >= 0 && pidCurrent <= processes.size());
            timeRun = 0; // new process means new timeRun
            
         }
         timeRun++;
      }
      // call the base-class which will handle a variety of housekeeping chores
      return Disbatcher::clock();
   }

  private:
   int timeQuantaDuration;
   int timeRun;
   std::queue <int> readyQueue;
};

#endif // SCHEDULE_RR
