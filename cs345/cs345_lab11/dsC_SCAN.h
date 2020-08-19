/***********************************************************************
* Component:
*    DISK SCHEDULING C-SCAN
* Author:
*    Jordan Jarvis
* Summary: 
*    This is the DERRIVED class to implement the SCAN algorithm
************************************************************************/

#ifndef DS_C_SCAN
#define DS_C_SCAN

#include "ds.h"   // for the DiskSchedulingAlgorithm base-class

// using namespace std;

/****************************************************
 * SCAN
 * The C-SCAN disk scheduling algorithm
 ***************************************************/
class DiskSchedulingC_SCAN : public DiskSchedulingAlgorithm
{
public:
   /*****************************************************
    * CONSTRUCTOR
    * initialize the data structures specific to SCAN
    *****************************************************/
   DiskSchedulingC_SCAN(const ScheduleProblem & problem) :
             DiskSchedulingAlgorithm(problem)
   {
      tempVar = 1000;
      tempVar2 = 0;
      requests = problem.requests;
      increase = problem.increasing;
      back = false;
      diskSize = problem.diskSize;
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
         if(increase)
         {
            // loop through all the requests and move to that location
            for (it = requests.begin(); it != requests.end(); ++it)
            {
               if (tempVar > computeDistance(*it) && *it > currentLocation)
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
                  tempVar = 1000;
                  tempVar2 = diskSize - 1;
                  break;
               }
               if(tempVar2 == diskSize - 1)
               {
                  tempVar2 = 0;
               }
            }
         }
         else
         {
            for (it = requests.begin(); it != requests.end(); ++it)
            {
               if (tempVar > computeDistance(*it) && *it < currentLocation)
               {
                  tempVar = computeDistance(*it);
                  tempVar2 = *it;
               }

            }
            currentLocation = tempVar2;
            record();
            if (tempVar2 == 0)
            {
               currentLocation = diskSize - 1;
               record();
            }

            for (it = requests.begin(); it != requests.end(); ++it)
            {
               if (tempVar2 == *it)
               {
                  requests.erase(it);
                  tempVar = 1000;
                  tempVar2 = 0;
                  break;
               }
               
            }
         }
      }
      return;
   }

private:
   std::list <int> requests;      // a copy of the list of disk requests
   int tempVar;
   int tempVar2;
   bool increase;
   bool back;
   int diskSize;
};

#endif // DS_SCAN
