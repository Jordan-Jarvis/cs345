/***********************************************************************
* Component:
*    DISK SCHEDULING SSTF
* Author:
*    Jordan Jarvis
* Summary: 
*    This is the DERRIVED class to implement the SSTF algorithm
************************************************************************/

#ifndef DS_SSTF
#define DS_SSTF

#include "ds.h"   // for the DiskSchedulingAlgorithm base-class

using namespace std;

/****************************************************
 * SSTF
 * The Sortest-Seek-Time-First disk scheduling algorithm
 ***************************************************/
class DiskSchedulingSSTF : public DiskSchedulingAlgorithm
{
public:
   /*****************************************************
    * CONSTRUCTOR
    * initialize the data structures specific to SSTF
    *****************************************************/
   DiskSchedulingSSTF(const ScheduleProblem & problem) :
             DiskSchedulingAlgorithm(problem)
   {
      int tempVar = 1000000;
      int tempVar2 = 0;
      requests = problem.requests;
      
   }

   /****************************************************
    * RUN
    * Implement the algorithm here. This function will only
    * be called once and will need to complete the entire
    * simulation.
    *
    * Each time a disk request is made by setting currentLocation,
    * call record() to save that.
    ***************************************************/
   void run()
   {
      std::list <int> :: iterator it;
      while(!requests.empty())
      {
         tempVar = 1000000;
         tempVar2 = 0;
         // loop through all the requests and move to that location
         for (it = requests.begin(); it != requests.end(); ++it)
         {
            if (tempVar > computeDistance(*it))
            {
               tempVar = computeDistance(*it);
               tempVar2 = *it;
            }
         }
         currentLocation = tempVar2;
         record();
         for (it = requests.begin(); it != requests.end(); ++it)
         {
            if (tempVar2 == *it)
            {
               requests.erase(it);
               tempVar = 1000000;
               break;
            }
         }
      }
      return;
   }

private:
   std::list <int> requests;      // a copy of the list of disk requests
   int tempVar;
   int tempVar2;
};

#endif // DS_SSTF
