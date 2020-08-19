/***********************************************************************
* Program:
*    Lab 04: Scheduling Lab
*    Brother Jones, CS 345
* Author:
*    your name
* Summary: 
*    This is the driver program to exercise the process thing.
*
*    Estimated:  0.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part.
************************************************************************/

#include <iostream>
#include <fstream>
#include <cassert>
#include "schedule.h"
using namespace std;

/*****************************************************************
 * MENU
 * Present the user with a menu from which he/she will select
 * the scheduling algorithm to use
 *****************************************************************/
ScheduleType menu()
{
   // present a list of options
   cout << "Please select one of the following scheduling algorithms:\n";
   cout << "  1. First-Come-First-Serve\n";
   cout << "  2. Round-Robin where Time Quanta is 1\n";
   cout << "  3. Round-Robin where Time Quanta is 4\n";
   cout << "  4. Shortest-Job-First non-preemptive\n";
   cout << "  5. Shortest-Remaining-Time\n";

   // prompt the user for a selection
   assert(cin.good());
   int input;
   cout << "> ";
   cin  >> input;
   while (cin.fail() || input < 1 || input > 5)
   {
      cout << "Error, invalid input. "
           << "Please select a number between 1 and 6: ";
      cin  >> input;
   }

   // return the type
   ScheduleType array[] =
   { // 0    1     2    3    4    5   
      FCFS, FCFS, RR1, RR4, SJF, SRT
   };
   assert(input >= 1 && input < sizeof(array)/sizeof(array[1]));
   return array[input];
}

/*********************************************************************
 * READ PROCESS FILE
 * Prompt the user for a filename containing the process list.
 * The format is: <name> <arrive time> <service time>
 * Example:
 *     A  0 3
 *     B  2 6
 *     C  4 4
 *     D  6 5
 *     E  8 2
 *********************************************************************/
bool readProcessFile(Disbatcher * p)
{
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
      return false;
   }

   char name[256];
   int  timeArrive;
   int  timeService;
   while (fin >> name >> timeArrive >> timeService)
      p->addProcess(Process(name, timeArrive, timeService));
   
   // close the file    
   fin.close();
   return true;
}

/**********************************************************************
 * MAIN
 * This is where it all begins
 ***********************************************************************/
int main()
{
   // select the scheduling algorithm
   Disbatcher * p = schedulerFactory(menu());

   // read the process info from a file
   if (!readProcessFile(p))
      return 1;

   // run the simulation
   p->runUntilDone();

   // display the results
   cout << *p << endl;

   // make like a tree
   delete p;   
   return 0;
}
