/***********************************************************************
* Component:
*    Process
* Author:
*    your name
* Summary: 
*    This is the base-class that enables various schedule algorithms
*    to simulate CPU Scheduling
************************************************************************/

#ifndef PROCESS
#define PROCESS

#include <string>     // for the name of the process

/**************************************
 * PROCESS
 * One process. It has a name, an arrival time, etc.
 *************************************/
class Process
{
public:
   // to create a process, you must know a few things
   Process(const std::string name, int timeArrival, int timeService)
   {
      this->name = name;
      this->timeArrival = timeArrival;
      this->timeService = timeService;
      this->timeLeft    = timeService;
      this->timeStart   = -1;
      this->timeFinish  = -1;
      this->started     = false;
   }

   // copy a process
   Process(const Process & rhs)
   {
      *this = rhs;
   }

   // copy a process
   Process & operator = (const Process & rhs)
   {
      name = rhs.name;
      timeArrival = rhs.timeArrival;
      timeService = rhs.timeService;
      timeLeft    = rhs.timeLeft;
      timeStart   = rhs.timeStart;
      timeFinish  = rhs.timeFinish;
      started     = rhs.started;
   }

   std::string getName() const
   {
      return name;
   }
   
   // display the statistics of a process
   friend std::ostream & operator << (std::ostream & out, const Process & rhs)
   {
      out << rhs.name;
      return out;
   }

   // has a process terminated?
   bool isDone() const
   {
      return timeLeft == 0;
   }

   // give this process some CPU time
   void execute(int time)
   {
      // take note if we just started
      if (!started)
      {
         started = true;
         timeStart = time;
      }
      
      assert(!isDone());
      timeLeft--;

      // take note if we just finished
      if (timeLeft == 0)
         timeFinish = time + 1;
   }

   // getters
   int getArrivalTime() const  { return timeArrival;  }
   int getServiceTime() const  { return timeService;  }
   int getTimeLeft()    const  { return timeLeft;     }
   int getFinishTime()  const  { return timeFinish;   }

   // how much time is left for this process?
   int getTurnaroundTime() const
   {
      return (timeFinish - timeArrival);
   }

   // determine how long this process waited
   int getWaitTime() const
   {
      assert(started);
      assert(timeFinish != 0);
      return getTurnaroundTime() - timeService;
   }

   // deterine running ratio
   float getRunningRatio() const
   {
      return (float)getTurnaroundTime() / (float)timeService;
   }
      
   
private:
   std::string name;   // the name. Usually one letter
   int timeArrival;    // when the process arrives to the scheduler
   int timeService;    // how long it will take for this process to execute
   int timeLeft;       // initially timeService, then 0 when completed
   int timeStart;      // when this process started
   int timeFinish;     // when this process finished
   bool started;       // did this process start yet?
};


#endif // PROCESS
