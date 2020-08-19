/***********************************************************************
* Component:
*    Page Replacement Basic
* Author:
*    Br. Helfrich
* Summary: 
*    This is the DERRIVED class to implement a basic page replacement algorithm
************************************************************************/

#ifndef PR_BASIC
#define PR_BASIC

#include <cassert>    // for ASSERT()
#include <cstdlib>    // for RAND() and SRAND()
#include <time.h>     // for TIME()
#include "pr.h"

#include <iostream>
using namespace std;

/****************************************************
 * BASIC
 * The simplest page replacement algorithm.
 ***************************************************/
class PageReplacementBasic : public PageReplacementAlgorithm
{
public:
   /*****************************************************
    * CONSTRUCTOR
    * initialize the data structures specific to BASIC
    *****************************************************/
   PageReplacementBasic(int numSlots) : PageReplacementAlgorithm(numSlots)
   {
      // seed the random number generator
      srand (time(NULL));
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
      // is pageNumber currently being used?
      for (int i = 0; i < getNumSlots(); i++)
         if (pageFrame[i] == pageNumber)
         {
            PageReplacementAlgorithm::record(pageNumber, false /*no fault*/);
            return;
         }

      // select the next victim
      int iNextVictim = rand() % getNumSlots();
      pageFrame[iNextVictim] = pageNumber;
      
      // call the record method so everything can be reported
      PageReplacementAlgorithm::record(pageNumber, true /*page fault*/);
      return;
   }

private:
   // which frame is selected to be next?
   int iNextVictim;
};

#endif // PR_BASIC
