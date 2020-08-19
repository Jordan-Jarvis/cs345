/***********************************************************************
* Component:
*    Page Replacement Second Chance
* Author:
*    Jordan Jarvis
* Summary: 
*    This is the DERRIVED class to implement Second
************************************************************************/

#ifndef PR_SECOND
#define PR_SECOND

#include "pr.h"   // for the PageReplacementAlgorithm base-class

#include <iostream>
using namespace std;

/****************************************************
 * Second Chance
 * The least-recently-used Approximation page replacement
 * algorithm known as Second Chance
 ***************************************************/
class PageReplacementSecond : public PageReplacementAlgorithm
{
public:
   /*****************************************************
    * CONSTRUCTOR
    * initialize the data structures specific to Second
    *****************************************************/
   PageReplacementSecond(int numSlots) : PageReplacementAlgorithm(numSlots)
   {
      iNextVictim = 0;
      lockdown = new bool[numSlots];
      for (int i = 0; i < numSlots; i++)
         lockdown[i] = false;
   }

   /****************************************************
    * RUN
    * Implement the LRU algorithm here. Thus function will get
    * called several times, each time requesting "pageNumber"
    * from memory. You are to assign that page to a "pageFrame"
    * and then call the base-class to record the results.
    ***************************************************/
   void run(int pageNumber)
   {                                                     
      for (int i = 0; i < getNumSlots(); i++)
      {
         if (pageFrame[i] == pageNumber)
         {
            PageReplacementAlgorithm::record(pageNumber, false /*no fault*/);
            lockdown[i] = true; // we have a hit
            return;
         }
      }
      while(true)
      {
         if (!lockdown[iNextVictim])
         {
            lockdown[iNextVictim] = true; // lock the page
            pageFrame[iNextVictim++] = pageNumber;
            if (iNextVictim >= getNumSlots())
               iNextVictim = 0;
            PageReplacementAlgorithm::record(pageNumber, true /*page fault*/);
            return;
         }
         else
         {
            lockdown[iNextVictim++] = false;
            if (iNextVictim >= getNumSlots())
               iNextVictim = 0; // reset them all if they are locked
         }
      }
   }

private:
   int iNextVictim;
   bool* lockdown;
};

#endif // PR_SECOND
