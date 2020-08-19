/***********************************************************************
* Component:
*    Scheduler
* Author:
*    your name
* Summary: 
*    This is the base-class that enables various schedule algorithms
*    to simulate CPU Scheduling
************************************************************************/

#ifndef SCHEDULER
#define SCHEDULER

#include <string>     // for the name of the process
#include <iostream>   // for the insertion operator
#include <iomanip>    // for setw
#include <vector>     // for the collection of processes
#include <cassert>    // because I am paranoid

#include "process.h"

enum ScheduleType { FCFS, RR1, RR4, SJF, SRT };
#define PID_NONE -1

/*****************************************************
 * DISBATCHER
 * The base-class for all the scheduling algorithms
 ****************************************************/
class Disbatcher
{
  public:
   Disbatcher() : time(0), pidCurrent(PID_NONE) {}
  
   // add a process, probably read from the file
   void addProcess(const Process & process)
   {
      processes.push_back(process);
   }

   // start a process. In other words, at this moment in time,
   // the process PID is ready for exection. This is a pure
   // virtual function because the derrived classes need to define this
   virtual void startProcess(int pid) = 0;

   // execute one clock cycle. The derived classes need to call this
   virtual bool clock();

   // run until done. In other words, carry out the simulation
   // until all the processes are finished
   void runUntilDone();
   
   // display the status of the scheduler
   friend std::ostream & operator <<
      (std::ostream & out, const Disbatcher & rhs);

protected:
   // have all the processes finished their job?
   bool isDone();

   // display 
   void displayProcessTable   (std::ostream & out) const;
   void displayStatisticsTable(std::ostream & out) const;
   void displayWaitStatistics (std::ostream & out) const;
   
   int  time;                         // timestamp
   std::vector <Process> processes;   // collection of all processes
   std::vector <int> history;         // which process was run and when
   int pidCurrent;                    // ID of the current process  
};

#include "scheduleFCFS.h"
#include "scheduleRR.h"
#include "scheduleSJF.h"
#include "scheduleSRT.h"

Disbatcher * schedulerFactory(ScheduleType st);

#endif // SCHEDULER
