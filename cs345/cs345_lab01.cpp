/***********************************************************************
* Program:
*    Lab 01, Submission Lab
*    Brother Comeau, CS345
* Author:
*    Jordan Jarvis
* Summary: 
*    This program counts the number of integers you enter until you put 
*    in a zero.
************************************************************************/

#include <iostream>
using namespace std;

/**********************************************************************
 * This is the main driver for the program and executes everything 
 * using a while loop.
 ***********************************************************************/
int main()
{
   int number = 0; //initialize variables
   int numberOfIntegers = 0;
   while (true) //always true until break is called
   {
      cout << "Enter an integer: ";
      cin >> number;
      if (number == 0)
      {
         if (numberOfIntegers == 0) // check if first input is 0
         {
            cout << "No non-zero integers were entered.\n";
            exit(0);
         }
         break;
      }
      numberOfIntegers++; // count number of integers entered
   }
   cout << "You entered " << numberOfIntegers << " integer";
   if (numberOfIntegers > 1)
      cout << "s.\n";
   else
      cout << ".\n"; // if only one then don't put in an s.
   return 0;
}

