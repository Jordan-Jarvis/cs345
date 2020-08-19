/***********************************************************************
* Component:
*    Page Replacement FIFO
* Author:
*    Jordan Jarvis
* Summary: 
*    This is the DERRIVED class to implement the FIFO algorithm
************************************************************************/

#ifndef PR_FIFO
#define PR_FIFO

#include "pr.h"   // for the PageReplacementAlgorithm base-class

#include <iostream>
#include <vector>
using namespace std;

/****************************************************
 * FIFO
 * The first-in, first-out page replacement algorithm
 ***************************************************/
class PageReplacementFIFO : public PageReplacementAlgorithm
{
public:
   /*****************************************************
    * CONSTRUCTOR
    * initialize the data structures specific to FIFO
    *****************************************************/
   PageReplacementFIFO(int numSlots) : PageReplacementAlgorithm(numSlots)
   {
      srand (time(NULL));
      int iNextVictim = 0;
   }

   /****************************************************
    * RUN
    * Implement the Basic algorithm here. Thus function will get
    * called several times, each time requesting "pageNumber"
    * from memory. You are to assign that page to a "pageFrame"
    * and then call the base-class to record the results.
    ***************************************************/
   void run(int pageNumber)
   {
      /////////////// YOUR CODE HERE ////////////////////

      // to place "pageNumber" in page 0
      
      for (int i = 0; i < getNumSlots(); i++)
         if (pageFrame[i] == pageNumber)
         {
            PageReplacementAlgorithm::record(pageNumber, false /*no fault*/);
            return;
         }

      // select the next victim

      pageFrame[iNextVictim++] = pageNumber;
      if(iNextVictim >= getNumSlots()){
         iNextVictim = 0;
      }
      // for no page fault
      // PageReplacementAlgorithm::record(pageNumber, false /*no fault*/);

      // for a page fault
      PageReplacementAlgorithm::record(pageNumber, true /*page fault*/);
      return;
   }

private:
int iNextVictim;
   //////////////////// YOUR CODE HERE //////////////////////
};

#endif // PR_BASIC
