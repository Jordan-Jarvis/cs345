/***********************************************************************
* Program:
*    Lab 09, MMU Lab
*    Brother Comeau, CS345
* Author:
*    Jordan Jarvis
* Summary: 
*    This program takes a text document with page table information
*    and maps virtual memory to physical memory.
************************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
using namespace std;

/**********************************************************************
 * Calulates page tables after reading them from a file.
 ***********************************************************************/
int main(int argc, char ** argv)
{

   string filename;
   int table[7][3];
   for(int i = 0; i < 8; i++)
   {
      table[i][0] = -1; // set all array values to 0
      table[i][1] = -1;
      table[i][2] = -1;

   }
   if (argc == 1)
   {
      cout << "What is the filename of the page table? ";
      cin >> filename;
   }
   else
   {
         filename = argv[1]; // if there is no command line argument
                              // ask for the filename
   }
   ifstream fin(filename);
   if (fin.fail())
   {
      cout << "Error reading file. ";
      return 0;
   }
   int pageSize;
   string temp;
   string temp1; // Create temporary strings
   string temp2;
   int logAddress;
   fin >> temp; // read in pageSize
   pageSize = atoi(temp.c_str()); // convert page size to int
   int i = 0;
   while(!fin.eof())
   {
      
      fin >> temp;
      fin >> temp1; // read in one line (3 chars separated by spaces)
      fin >> temp2;
      if (temp == "-1")
      {
         break; // check if the line is empty
      }
      table[i][0] = atoi(temp.c_str());
      table[i][1] = atoi(temp1.c_str()); // convert strings to ints
      table[i][2] = atoi(temp2.c_str());
      cerr << table[i][0] << " " << table[i][1] << " " << table[i][2] << endl;
      i++; // iterate
      temp = "-1"; // set to 0 to check for empty line
      }
   cout << "Enter logical address and the corresponding physical one will be displayed.\n";
   cout << "Enter 0 for an address when done.\n";
   int tableSize = 0;
   tableSize = sizeof(table) / sizeof(table[0]); // variables for calculation
   int arrayPos = -1;
   int logicalPageNumber = 0;
   while (true)
   {
      cout << "> ";

      cin >> logAddress;
      if(logAddress == 0) // exit if the uer enters 0
         break;
      logicalPageNumber = logAddress / pageSize;
      for (int t = 0; t < tableSize; t++)
      {
         if(table[t][0] == logicalPageNumber) // find the logicalPagenumber array position.
         {
            arrayPos = t;
            break;
         }
      }
      if (arrayPos == -1)
      {
         cout << "error"; // detect invalid values
      }
      if (table[arrayPos][1])
         cout << "\t" << table[arrayPos][2] * pageSize + (logAddress % pageSize) << endl;
      else
         cout << "\tPage Fault\n"; // print the value or error with page fault if valid 
         //bit is equal to 0
   }
   fin.close();
   return 0;
}

