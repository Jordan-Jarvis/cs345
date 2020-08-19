/***********************************************************************
* Component:
*    DISK SCHEDULING LOOK
* Author:
*    Jordan Jarvis
* Summary: 
*    This is the DERRIVED class to implement the LOOK algorithm
************************************************************************/

#ifndef DS_LOOK
#define DS_LOOK

#include "ds.h"   // for the DiskSchedulingAlgorithm base-class

// using namespace std;

/****************************************************
 * SCAN
 * The LOOK (SCAN with lookahead) disk scheduling algorithm
 ***************************************************/
class DiskSchedulingLOOK : public DiskSchedulingAlgorithm
{
public:
   /*****************************************************
    * CONSTRUCTOR
    * initialize the data structures specific to SCAN
    *****************************************************/
   DiskSchedulingLOOK(const ScheduleProblem & problem) :
             DiskSchedulingAlgorithm(problem)
   {
      /////////////// YOUR CODE HERE ////////////////////
      requests = problem.requests;
      increasing = problem.increasing;
      diskSize = problem.diskSize;
      tempVar = 1000;
      tempVar2 = 0;
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
      /////////////// YOUR CODE HERE ////////////////////
     
      std::list <int> :: iterator it;
      while(!requests.empty()){
         if (increasing){
            for (it = requests.begin(); it != requests.end(); ++it)
            {
               if (tempVar > computeDistance(*it) && *it > currentLocation)
               {
                  tempVar = computeDistance(*it);
                  tempVar2 = *it;  
               }
               
            }
            if(tempVar2 != (diskSize - 1))
            {
               currentLocation = tempVar2;
               record();
            }
         
            for (it = requests.begin(); it != requests.end(); ++it)
            {
               if (tempVar2 == *it)
               {      
                  requests.erase(it);
                  tempVar = 1000; 
                  tempVar2 = diskSize - 1;
                  break;
               }
               else if (tempVar2 == (diskSize - 1))
               {
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
               }
            }
         }
         else if (!increasing)
         {
            for (it = requests.begin(); it != requests.end(); ++it)
            {
               if (tempVar > computeDistance(*it) && *it < currentLocation)
               {
                  tempVar = computeDistance(*it);
                  tempVar2 = *it;  
               }
               
            }
            if(tempVar2 != 0)
            {
               currentLocation = tempVar2;
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
               else if (tempVar2 == 0)
               {
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
               }
            }
         }
      }
      return;
   }

private:
   std::list <int> requests; 
   bool increasing;
   int diskSize;
   int tempVar;
   int tempVar2;
};

#endif // DS_LOOK
