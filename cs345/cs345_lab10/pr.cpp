/***********************************************************************
* Component:
*    Page Replacement
* Author:
*    Br. Helfrich
* Summary: 
*    This will implement a few helper functions.
*
*    Note that you do not need to change this to any capacity
************************************************************************/

#include <iostream>   // for the insertion operator
#include <cassert>    // because I am paranoid
#include "pr.h"       // for the PageReplacementAlgorithm class definition

using namespace std;

/**************************************************
 * RECORD
 * Record the result of a single page request
 **************************************************/
void PageReplacementAlgorithm::record(int pageNumber, bool fault)
{
   // record the entire page frame
   historyPF.push_back(pageFrame);

   // record which page number was requested at this moment in time
   historyRS.push_back(pageNumber);

   // record whether there was a page fult
   historyF.push_back (fault);
   numFaults += (fault ? 1 : 0);
}
   
/**********************************************
 * DISPLAY
 * Display the history of all the executions
 **********************************************/
ostream & operator << (ostream & out, const PageReplacementAlgorithm & rhs)
{
   int num = rhs.historyRS.size();
   assert(rhs.historyPF.size() == rhs.historyRS.size());

   // display the top row first
   list <int> :: const_iterator itRS;
   for (itRS = rhs.historyRS.begin(); itRS != rhs.historyRS.end(); ++itRS)
      out << *itRS << ' ';
   out << endl;

   // display the top bar
   for (int i = 0; i < num; i++)
      out << "+-";
   out << "+\n";

   // display each slot in turn
   for (int iSlot = 0; iSlot < rhs.numSlots; iSlot++)
   {
      list < std::vector <int> > :: const_iterator itPF;
      for (itPF = rhs.historyPF.begin(); itPF != rhs.historyPF.end(); ++itPF)
      {
         out << '|';
         if (itPF->operator[](iSlot) == -1)
            out << ' ';
         else
            out << itPF->operator[](iSlot);
      }
      out << "|\n";
   }

   // display the bottom bar
   for (int i = 0; i < num; i++)
      out << "+-";
   out << "+\n";

   // display the history of the page faults
   list <bool> :: const_iterator itF;
   for (itF = rhs.historyF.begin(); itF != rhs.historyF.end(); ++itF)
      out << ' ' << (*itF ? 'F' : ' ');
   out << endl;

   // display the hit ratio
   out << "Hit ratio: " << (num - rhs.numFaults) << '/' << num << endl;

   return out;
}
   
/*****************************************************
 * Page Replacement FACTORY
 * Create an instance of a Page Replacement Algorihtm that implements
 * a specific algorithm
 *****************************************************/
PageReplacementAlgorithm * prFactory(PageReplacementType prt, int numSlots)
{
   switch (prt)
   {
      case BASIC:
         return new PageReplacementBasic (numSlots);
      case FIFO:
         return new PageReplacementFIFO  (numSlots);
      case LRU:
         return new PageReplacementLRU   (numSlots);
      case SECOND:
         return new PageReplacementSecond(numSlots);
   }

   assert(false);
   return new PageReplacementBasic(numSlots);   
}
