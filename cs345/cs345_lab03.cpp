/***********************************************************************
* Program:
*    Lab 03, Shell Lab
*    Brother Comeau, CS 345
* Author:
*    Jordan Jarvis
* Summary:
*    Simple command line program, uses threads to run processes and keeps
*    a memory of the commands already run. StyleChecker was having issues
*    when I ran it, i kept having it exit with an error.
************************************************************************/
#include <signal.h>
#include <iostream>
#include <iomanip>
#include <signal.h>
#include <cstring>
#include <unistd.h>
#include <wait.h>
#include <sstream>
#include <cstdlib>
#include <stdio.h>
#define MAX_LINE 80 /* 80 chars per line, per command, should be enough. */
#define BUFFER_SIZE 50
#define HIST_SIZE 10

/* Maximum number of commands until count rolls over. */
#define MAX_NUM_CMDS 1000

using namespace std;
string commands[HIST_SIZE];
int goodStringCount = 0;

/************************************************************************
* handles static char for passing through program
************************************************************************/
static char msg4handler2print[BUFFER_SIZE];
      
/*************************************************************************
* adds a command to the history
**************************************************************************/
void add2History (string input)
{
   commands[goodStringCount % HIST_SIZE] = input;
   goodStringCount++;  

   // Roll over the count if it hits the maximum allowed for printing 
   if ( goodStringCount >= MAX_NUM_CMDS )
      goodStringCount = HIST_SIZE;    /* Leave a full buffer of commands */
}
      
/*************************************************************************
* findCommandInHistory() searches backward for the first command that
* begins with a particular character (char c) in the history buffer.
* If a string is found that begins with the character, the string is
* passed back to the calling function.  If the character being looked
* for is a NULL then the most recent command is returned.  In both of
* the preceeding cases, the return value is set to true.  If no matching
* string is found, the return value is set to false.
**************************************************************************/
bool findCommandInHistory(char c, string& stringFound)
{
   int temp = goodStringCount;
   stringFound = "";

   // If the character being looked for is a null, then return the most
   // recent command, if there was one.
   if (c == '\0')
   {
      if (goodStringCount)
      {
         stringFound = commands[ (goodStringCount - 1) % HIST_SIZE ];
         return true;
      }
      else
      {
         return false; 
      }
   }
   
   // Look back through the history for a command staring with the letter
   // given in the first argument to this function.
   for (temp; temp >= 0 && temp != temp - HIST_SIZE; --temp)
   {            
      if (commands[temp % HIST_SIZE][0] == c)
      {
         stringFound = commands[temp % HIST_SIZE];
         return true;
      }
   }
         
   return false;
}


/*************************************************************************
* Display the contents of the history buffer of commands with the number
* of the command listed on the beginning of the line.
**************************************************************************/
void displayHistory( )
{
   int start;
   
   if (goodStringCount > HIST_SIZE)
      start = goodStringCount - HIST_SIZE;
   else
      start = 0;

   for (int i = start; i < goodStringCount; ++i)
   {            
      cout << " " << setw(3) << i << "  " << commands[i % HIST_SIZE] << endl;
   }
   
   return;
}


/***************************************************************************
 * SETUP
 * setup() reads in the next command line, separating it into distinct tokens
 * using whitespace as delimiters.
 *
 * setup() modifies the inputBuffer creating a set of null-terminated strings
 * and places pointers into the args[] array that point to the beginning of
 * each argument.  A NULL pointer is placed in the args[] array indicating
 * the end of the argument list.  This is what is needed for using execvp().
 *
 * A ^d input at the beginning of a line, by a user, exits the shell.
 **************************************************************************/
bool setup(char inputBuffer[], char * args[], int * background, bool goodCmd)
{
   int length; // # of characters in the command line 
   int i;      // loop index for accessing inputBuffer array 
   int start;  // index where beginning of next command parameter is 
   int ct;     // index of where to place the next parameter into args[] 
   string tmpString;
   ct = 0;
    
   /* read what the user enters on the command line */
   length = read(STDIN_FILENO, inputBuffer, MAX_LINE); 
   
   
   
   
   
   start = -1;            /* Used as a flag to indicate that we are looking
                           * for the start of the command or an argument if
                           * it is a -1, or stores the starting position of
                           * the command or argument to be put in args[].
                           */
   if (length == 0)
      exit(0);            /* ^d was entered, end of user command stream */
   if (length < 0)
   {
      perror("error reading the command");
      exit(-1);           /* terminate with error code of -1 */
   }

   /* examine every character in the inputBuffer */
   for (i = 0; i < length; i++)
   { 
      switch (inputBuffer[i])
      {
         case ' ':
         case '\t' :               /* argument separators */
            if (start != -1)        /* found the end of the command or arg */
            {
               args[ct] = &inputBuffer[start]; /* set up pointer in args[] */
               ct++;
            }
            inputBuffer[i] = '\0'; /* add a null char; make a C string */
            start = -1;
            break;

         case '\n':                 /* should be the final char examined */
            if (start != -1)        /* if in the command or an argument */
            {
               args[ct] = &inputBuffer[start]; /* set up pointer in args[] */ 
               ct++;
            }
            inputBuffer[i] = '\0';
            args[ct] = NULL; /* no more arguments to this command */
            break;

         default :             /* some other character */
            if (start == -1 && inputBuffer[i] != '&')
               start = i;      /* starting position of the command or arg */
            if (inputBuffer[i] == '&')
            {
               *background  = 1;
               inputBuffer[i] = '\0';
            }
      }  // end of switch
   }  // end of for loop looking at every character 
   
   inputBuffer[length - 1] = '\0';
   if ( length == 1 )
   {
         // If the user just entered a newline, then the length of the
         // input will be 1 and we just want to give the prompt again.
         // (Ignoring the newline input.)
      goodCmd = false;
   }
   else if (inputBuffer[0] == '.' && inputBuffer[1] == '\0')
   {
      displayHistory( );
      goodCmd = false;
   }
   else if ( length == 0 || (! strncmp( inputBuffer, "exit", MAX_LINE )) )
   {
      // End of file or exit command given
      exit(0);
   }
   else if (inputBuffer[0] == 'r' && 
      (inputBuffer[1] == '\0' || inputBuffer[1] == ' ') )
   {         
         // If an 'r' command was given and a matching command is found in the
         // history, then put the command to be repeated in the buffer.
         // If an 'r' was given with no argument the most recent command
         // should be executed.  This is indicated with a null.
      if (inputBuffer[1] == '\0') inputBuffer[2] = '\0';
      goodCmd = findCommandInHistory(inputBuffer[2], tmpString);

      if ( goodCmd )
      { 
         strncpy (inputBuffer, tmpString.c_str(), MAX_LINE);
      }
      else
      {
         cout << "Command not found\n";
         cout.flush();   
      }
         
   }
   if ( goodCmd )
   {
      add2History( (string) inputBuffer );
   }
   args[ct] = NULL; /* just in case the input line was > 80 */
   return goodCmd;
} 

/*************************************************************
*  the signal handler function
*   note: If compiling this with gcc the definition may be:
*             void handle_SIGUSR1()
*         For g++ this works:   void handle_SIGUSR1( int )
*         Both gcc and g++ like:   void handle_SIGUSR1( int junk )
**************************************************************/
void handle_SIGUSR1( int junk )
{
   cout << "\n";
   displayHistory();
   exit(0);
   // this handler could exit, but typically would return so that you
    // continue execution of the program after handling the signal.
   //exit(0);
   return; 
}

/*************************************************************************
* Display the contents of the history buffer of commands with the number
* of the command listed on the beginning of the line.
**************************************************************************/
int main(int argc, char * argv[])
{
   struct sigaction handler;
   handler.sa_flags = SA_RESTART;
   handler.sa_handler = handle_SIGUSR1;   /* function the handler will call */
   sigaction(SIGUSR1, &handler, NULL);    /* handler to call for USR1 signal */
   sigaction(SIGQUIT, &handler, NULL);
   /* set up the message we want printed when USR1 is seen */
   strncpy( msg4handler2print, "Caught signal USR1\n", BUFFER_SIZE );
   int length = -1;
   bool goodCmd;

   char inputBuffer[MAX_LINE]; /* buffer to hold the command entered */
   int background;             /* equals 1 if a command is followed by '&' */
   char *args[MAX_LINE / 2];   // command line (of 80) has max of 40 arguments
   pid_t c_pid, pid;
   int status;

   while (1)                   /* Program terminates normally inside setup */
   {
      length = -1;
      goodCmd = true; // reset variables in the loop
      background = 0;
      printf(" COMMAND-> "); 
      fflush(stdout);
      
      do   //run setup
      {
         goodCmd = setup(inputBuffer, args, &background, &goodCmd);  
         
      } while (background < 0);
      if (goodCmd == false)
      {
         continue;
      }
      c_pid = fork();
      //fork the program to allow concurrent processes to run
      if (c_pid == 0 )
      {   
         if (execvp(inputBuffer, args) < 0) // execute the command
         {     
            printf("*** ERROR: exec failed\n");
            exit(1);
         }
      }
      else if ((c_pid > 0) && (background != 1))
      {
             // Code only executed by parent process
         wait(&status);
      }
      else
      {
         perror("fork failed");
         _exit(1);
      }
   }
}

