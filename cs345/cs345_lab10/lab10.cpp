/***********************************************************************
* Program:
*    Lab 10: Page Replacement Lab
*    <your instructor>, CS 345
* Author:
*    <your name>
* Summary: 
*    This is the driver program to exercise the page replacement algorithm
*
*    Estimated:  0.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part.
************************************************************************/

#include <iostream>
#include <fstream>
#include <cassert>
#include <list>
#include "pr.h"
using namespace std;

/*****************************************************************
 * MENU
 * Present the user with a menu from which he/she will select
 * the scheduling algorithm to use
 *****************************************************************/
PageReplacementType menu()
{
   // present a list of options
   cout << "Please select one of the following page replacement algorithms:\n";
   cout << "  1. Basic Page Replacement\n";
   cout << "  2. First-In-First-Out\n";
   cout << "  3. Least Recently Used\n";
   cout << "  4. Second Chance\n";

   // prompt the user for a selection
   assert(cin.good());
   int input = 1;
   cout << "> ";
   cin  >> input;
   while (cin.fail() || input < 1 || input > 4)
   {
      cout << "Error, invalid input. "
           << "Please select a number between 1 and 4: ";
      cin  >> input;
   }

   // return the type
   PageReplacementType array[] =
   { // 0    1      2      3     4
      BASIC, BASIC, FIFO,  LRU,  SECOND
   };
   assert(input >= 1 && input < sizeof(array)/sizeof(array[1]));
   return array[input];
}

/*********************************************************************
 * READ REFERENCE STRING
 * Prompt the user for a filename containing the reference string.
 * This string is just a list of page numbers
 * Example:
 *     1 0 2 2  1 7 6 7  0 1 2 0  3 0 4 5  1 5 2 4  5 6 7 6  7 2 4 2  7 3 3 2 
 *********************************************************************/
list <int> readReferenceString()
{
   list <int> output;
   
   // prompt for filename
   char fileName[256];
   cout << "What is the filename of the process file? ";
   cin  >> fileName;

   // open the file
   ifstream fin(fileName);
   if (fin.fail())
   {
      cout << "Unable to open file '"
           << fileName
           << "', exiting.\n";
      return output;
   }

   // actually read the data from the file
   int page;
   while (fin >> page)
      output.push_back(page);
   
   // close the file    
   fin.close();
   return output;
}

/**********************************************************************
 * MAIN
 * This is where it all begins
 ***********************************************************************/
int main()
{
   // determine the number of pages in each frame
   int numSlots = 3;
   cout << "How many slots: ";
   cin  >> numSlots;
   
   // read the process info from a file
   list <int> referenceString = readReferenceString();
   if (referenceString.size() == 0)
      return 1;

   // select the page replacement algorithm
   PageReplacementAlgorithm * p = prFactory(menu(), numSlots);

   // run the simulation
   list <int> :: iterator it;
   for (it = referenceString.begin(); it != referenceString.end(); ++it)
      p->run(*it);

   // display the results
   cout << *p;

   // make like a tree
   delete p;   
   return 0;
}
