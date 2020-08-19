/***********************************************************************
* Component:
*    Scheduler
* Author:
*    your name
* Summary: 
*    This is the base-class that enables various schedule algorithms
*    to simulate CPU Scheduling
*
*    Note that you do not need to change this to any capacity
************************************************************************/

#include <string>     // for the name of the process
#include <iostream>   // for the insertion operator
#include <iomanip>    // for setw
#include <vector>     // for the collection of processes
#include <cassert>    // because I am paranoid
#include "schedule.h"

using namespace std;

/**************************************************
 * RUN UNTIL DONE
 * Execute the CPU simulator until we have finished
 * all of the proceses
 **************************************************/
void Disbatcher::runUntilDone()
{
   assert(pidCurrent == PID_NONE ||
          (pidCurrent >= 0 && pidCurrent < (int)processes.size()));

   // handle the initial condition when we there are processes running
   for (int pid = processes.size() - 1; pid >= 0; pid--)
      if (processes[pid].getArrivalTime() == time)
         startProcess(pid);
   
   // continue until we have learned that all the processes are done
   while(clock())
      ;
}
   
/************************************************
 * CLOCK
 * Execute one clock cycle. This should be called
 * from all the derived classes
 ***********************************************/
bool Disbatcher::clock()
{
   // paranoia
   assert(pidCurrent == PID_NONE ||
          (pidCurrent >= 0 && pidCurrent < (int)processes.size()));

   // if there is a process currently selected, then execute it
   if (pidCurrent != PID_NONE)
      processes[pidCurrent].execute(time);
   
   // remember who is currently running
   history.push_back(pidCurrent);

   // advance time by one
   time++;

   // done another process need to be added?
   for (int pid = 0; pid < processes.size(); pid++)
      if (processes[pid].getArrivalTime() == time)
         startProcess(pid);

   // indicate whether all of the processes are done
   return !isDone();
}

/*************************************************
 * DISPLAY PROCESS TABLE
 * Display the process table in all its ASCII-ART glory
 ************************************************/
void Disbatcher::displayProcessTable(ostream & out) const
{
   // display the header
   out << "   ";
   for (int iTime = 0; iTime < history.size(); iTime++)
      out << setw(3) << iTime;
   out << endl;
   
   // display each process in turn
   for (int pid = 0; pid < processes.size(); pid++)
   {
      out << ' '
          << processes[pid].getName()
          << ' ';
      for (int iTime = 0; iTime < history.size(); iTime++)
         out << setw(3)
             << (history[iTime] == pid ? '#' : ' ');
      out << endl;
   }
}

/*****************************************************
 * DISPLAY STATISTICS TABLE
 * Display the statistics table on the screen
 ****************************************************/
void Disbatcher::displayStatisticsTable(ostream & out) const
{
   out << "   "
       << setw(17) << "Finish Time"
       << setw(17) << "Turnaround Time"
       << setw(17) << "Running Ratio"
       << endl;

   // display each process in turn
   out.setf(ios::fixed | ios::showpoint);
   out.precision(1);
   float turnaround = 0.0;
   float ratio = 0.0;
   for (int pid = 0; pid < processes.size(); pid++)
   {
      out << ' '
          << processes[pid].getName()
          << ' '
          << setw(17) << processes[pid].getFinishTime()
          << setw(17) << processes[pid].getTurnaroundTime()
          << setw(17) << processes[pid].getRunningRatio()
          << endl;
      turnaround += processes[pid].getTurnaroundTime();
      ratio      += processes[pid].getRunningRatio(); 
   }

   out << "   "
       << setw(17) << "mean:"
       << setw(17) << (turnaround / processes.size())
       << setw(17) << (ratio      / processes.size())
       << endl;
}

/***********************************************
 * DIPSLAY WAIT STATISTICS
 * Display the total and average wait time
 **********************************************/
void Disbatcher::displayWaitStatistics(std::ostream & out) const
{
   // compute the total wait time
   int timeTotalWait = 0;
   for (int pid = 0; pid < processes.size(); pid++)
      timeTotalWait += processes[pid].getWaitTime();

   // display the wait statistics
   out.setf(ios::fixed | ios::showpoint);
   out.precision(1);
   out << "Total wait time:   "
       << timeTotalWait
       << endl;
   out << "Average wait time: "
       << (float)timeTotalWait / (float)processes.size()
       << endl;
}

/**********************************************
 * DISPLAY
 * Display the history of all the executions
 **********************************************/
ostream & operator << (ostream & out, const Disbatcher & rhs)
{
   // display the process table
   out << endl << endl
       << "Process Table\n";
   rhs.displayProcessTable(out);

   // display the statistics table
   out << endl << endl
       << "Statistics Table\n";
   rhs.displayStatisticsTable(out);

   // display the wait statistics
   out << endl << endl
       << "Wait Statistics\n";
   rhs.displayWaitStatistics(out);
   return out;
}
   
/*************************************************
 * IS DONE
 * Determine whether all the processes have run their course
 *************************************************/
bool Disbatcher::isDone()
{
   // iterate through all the processes
   for (vector <Process> :: iterator it = processes.begin();
        it != processes.end();
        ++it)

      // if one is not done, then we are not done
      if (!(it->isDone()))
         return false;

   // if all are complete, then we are done
   return true;
}

/*****************************************************
 * SCHEDULER FACTORY
 * Create an instance of a schedule method that implements
 * a specific scheduling algorithm
 *****************************************************/
Disbatcher * schedulerFactory(ScheduleType st)
{
   switch (st)
   {
      case FCFS:
         return new SchedulerFCFS;
      case RR1:
         return new SchedulerRR(1);
      case RR4:
         return new SchedulerRR(4);
      case SJF:
         return new SchedulerSJF;
      case SRT:
         return new SchedulerSRT;
   }

   assert(false);
   return new SchedulerFCFS;   
}
