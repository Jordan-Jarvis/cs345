/***********************************************************************
* Component:
*    DISK SCHEDULING C-LOOK
* Author:
*    Jordan Jarvis
* Summary: 
*    This is the DERRIVED class to implement the C-LOOK algorithm
************************************************************************/

#ifndef DS_C_LOOK
#define DS_C_LOOK

#include "ds.h"   // for the DiskSchedulingAlgorithm base-class

//using namespace std;

/****************************************************
 * C-LOOK
 * The C-LOOK disk scheduling algorithm
 ***************************************************/
class DiskSchedulingC_LOOK : public DiskSchedulingAlgorithm
{
public:
   /*****************************************************
    * CONSTRUCTOR
    * initialize the data structures specific to C-LOOK
    *****************************************************/
   DiskSchedulingC_LOOK(const ScheduleProblem & problem) :
     DiskSchedulingAlgorithm(problem)
   {
      requestSet = problem.requests;
      goUp = problem.increasing;
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
      std::list <int> :: iterator it;
      while(!requestSet.empty()){
         if (goUp)
         {
            for (it = requestSet.begin(); it != requestSet.end(); ++it)
            {
               if (tempVar > computeDistance(*it) && *it > currentLocation)
               {
                  tempVar = computeDistance(*it);
                  tempVar2 = *it;  
               }
            }
            if(tempVar2 != (diskSize - 1) && tempVar2 != 0)
            {
               currentLocation = tempVar2;
               record();
            }
            if(tempVar2 == 0)
            {
               currentLocation = tempVar2;
            }
            for (it = requestSet.begin(); it != requestSet.end(); ++it)
            {
               if (tempVar2 == *it)
               {      
                  requestSet.erase(it);
                  tempVar = 1000; 
                  tempVar2 = diskSize - 1;
                  break;
               }
               if(tempVar2 == (diskSize - 1))
               {
                  tempVar2 = 0;
               }
            }
         }
         else if (!goUp)
         {
            for (it = requestSet.begin(); it != requestSet.end(); ++it)
            {
               if (tempVar > computeDistance(*it) && *it < currentLocation)
               {
                  tempVar = computeDistance(*it);
                  tempVar2 = *it;  
               }
            }
            if(tempVar2 != (diskSize - 1) && tempVar2 != 0)
            {
               currentLocation = tempVar2;
               record();
            }
            if(tempVar2 == 0)
            {
               currentLocation = diskSize - 1;
            }
         
            for (it = requestSet.begin(); it != requestSet.end(); ++it)
            {
               if (tempVar2 == *it)
               {      
                  requestSet.erase(it);
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
   std::list <int> requestSet; 
   bool goUp;
   int diskSize;
   int tempVar;
   int tempVar2;
};

#endif // DS_C_LOOK
