/***********************************************************************
* Component:
*    Page Replacement LRU
* Author:
*    Jordan Jarvis
* Summary: 
*    This is the DERRIVED class to implement LRU
************************************************************************/

#ifndef PR_LRU
#define PR_LRU

#include "pr.h"   // for the PageReplacementAlgorithm base-class

#include <iostream>
using namespace std;

/****************************************************
 * SRL
 * The least-recently-used page replacement algorithm
 ***************************************************/
class PageReplacementLRU: public PageReplacementAlgorithm
{
public:
   /*****************************************************
    * CONSTRUCTOR
    * initialize the data structures specific to LRU
    *****************************************************/
   PageReplacementLRU(int numSlots) : PageReplacementAlgorithm(numSlots)
   {
      
      for (int i = 0; i <= getNumSlots(); i++)
      {
            ages[i] = -1;
      }
      //////////////// YOUR CODE HERE ////////////////////      
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
      temp = -1;
      /////////////// YOUR CODE HERE ////////////////////
      for (int i = 0; i < getNumSlots(); i++)
      {
         if (pageFrame[i] != -1){
            ages[i] = ages[i] + 1;
         }
         if (pageFrame[i] == pageNumber)
         {
            temp = i;
         }

      }

      if (temp > -1)
      {
         ages[temp] = 0;
         PageReplacementAlgorithm::record(pageNumber, false /*no fault*/);
         return;
      }
      temp = -1;
      temp2 = 0;
      for (int i = 0; i < getNumSlots(); i++)
      {
         if(pageFrame[i] == -1)
         {
            pageFrame[i] = pageNumber;
            ages[i] = 0;
            PageReplacementAlgorithm::record(pageNumber, true /*page fault*/);
            return;
         }
         if (ages[i] > temp)
         {
            temp = ages[i];
            temp2 = i;
         }
      }
      ages[temp2] = 0;
      pageFrame[temp2] = pageNumber;
      PageReplacementAlgorithm::record(pageNumber, true /*page fault*/);
      return;      
   }

private:
   int temp;
   int temp2;
   int* ages = new int[getNumSlots()];
      
   //////////////////// YOUR CODE HERE //////////////////////
};

#endif // PR_LRU
