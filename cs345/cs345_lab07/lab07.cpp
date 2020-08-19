/***********************************************************************
 * Program:
 *    Lab 06, Producer and Consumer
 * Author:
 *    Jordan Jarvis
 * Summary:
 *    This program will allow us to simulate the production run
 *    at McLaren Cars. It would be cool if it simulated the cars
 *    themselves, but that might be an assignment for another day
 *
 *    Note that you must compile this with the -lpthread switch:
 *        g++ -lpthread lab06.cpp
 ************************************************************************/

#include <iostream>      // for COUT
#include <cassert>       // for ASSERT 
#include <string>        // for STRING
#include <sstream>       // for STRINGSTREAM
#include <queue>         // for QUEUE
#include <ctime>         // for time(), part of the random process
#include <unistd.h>      // for usleep()
#include <stdlib.h>      // for rand() and srand()
#include "cars.h"        // for everything dealing with McLaren Cars
#include <semaphore.h>
#include <pthread.h>

using namespace std;
pthread_mutex_t mutex;
// This variable represents the shared memory between the parent thread
// and all the children. Recall from the reading how the main way for
// threads to communicate is through shared memory. This shared memory
// needs to be global.
sem_t sema; // sem
sem_t filledSpaces;
sem_t emptySpaces;
bool productionComplete = false;

void   *  producer(void * param);   // modified to work thread safe
void * consumer(void * param);   // modified to work thread safe

int getNumber(const char * prompt, int max);
Inventory inventory;
struct v
{
   string model;
   string sout;
};
/***********************************************
 * MAIN
 * This will serve to prompt the user for the number
 * of models and the number of retailers. It will then
 * begin the simulation
 ***********************************************/
int main(int argc, char **argv)
{
   // set up the random number generator
   srand(argc == 1 ? time(NULL) : (int)argv[1][1]);
   if (sem_init(&filledSpaces, 0, 0) != 0)
    {
        printf("\n sem init failed\n");
        return 1;
    }
    
    if (sem_init(&emptySpaces, 0, 6) != 0)
    {
        printf("\n sem init failed\n");
        return 1;
    }
   if (pthread_mutex_init(&mutex,NULL) !=0)
      return 1;
   // determine how many producer and consumer threads
   int numProducer = getNumber("How many models?    ", numModels());
   int numConsumer = getNumber("How many retailers? ", numRetailers());

   // produce the cars. Note that this code needs to change. We will
   // need to launch one thread per producer here
   pthread_t *tID = new pthread_t[numProducer];
   pthread_t *tID2 = new pthread_t[numConsumer];
   v *producerParams = new v[numProducer];
   v *consumerParams = new v[numConsumer];


   for (int i = 0; i < numProducer; i++)
   {
      //struct v *mData = (struct v*) malloc(sizeof(struct v));
      producerParams[i].model = models[i];

      pthread_t tid;
      pthread_attr_t attr; // start the thread and init everything
      pthread_attr_init(&attr);
      pthread_create(&tid, &attr, producer, &producerParams[i]);
      tID[i] = tid;
   }
   // sell the cars. Note that this code also needs to change.
   cout << "\nThe cars sold from the various retailers:\n\n";
   for (int i = 0; i < numConsumer; i++)
   {

      //struct v *mData = (struct v*) malloc(sizeof(struct v));
      consumerParams[i].model = retailers[i];
      pthread_t tid;
      pthread_attr_t attr; // start the thread and init everything
      pthread_attr_init(&attr);
      pthread_create(&tid, &attr, consumer, &consumerParams[i]);
      tID2[i] = tid;
   }
            
   for(int i=0;i < numProducer;i++) // join the producers
   {
      pthread_join(tID[i], NULL);      
   }
   for(int i = 0; i < numConsumer;i++) // join the consumers
   {
      pthread_join(tID2[i], NULL);
      cout << consumerParams[i].sout << endl;
   }

      cout << "Maximum size of the inventory: "
        << inventory.getMax()
        << endl;
   return 0;
}

/***********************************************************
 * PRODUCER
 * Create those cars.
 * This function is not currently thread safe. You will need
 * to introduce a critical section in such a way that we do
 * not compromise the queue nor produce two cars with the
 * same serial number.
 **********************************************************/
void *producer(void *param)
{
   v *mData = (v*) param;
   
   static int serialNumberNext = 0;
   // a car to be added to the inventory
   Car car;
   const char *c = mData->model.c_str();
   car.model = c;
   int numcars = NUM_CARS;

   // continue as long as we still need to produce cars in this run
   while (serialNumberNext < NUM_CARS)
   {

      
      // now that we decided to build a car, it takes some time
      usleep(rand() % 150000);
      
      sem_wait(&emptySpaces);

      // add the car to our inventory if we still need to
      if (serialNumberNext < NUM_CARS)
      {
         
         pthread_mutex_lock(&mutex);
         car.serialNumber = ++serialNumberNext;

         
         inventory.makeCar(car);
         pthread_mutex_unlock(&mutex);
      }
      sem_post(&filledSpaces);
   }

   // all done!

   productionComplete = true;
   pthread_exit(0);
}

/***********************************************************
 * CONSUMER
 * Sell those cars.
 * This function is not currently thread safe. You will need
 * to introduce a critical section in such a way that we
 * do not compromise the queue nor sell the same car twice.
 **********************************************************/
void * consumer(void * param)
{

   v *mData = (v*) param;
   

   const char *c = mData->model.c_str();
   string retailer = c;

   // collect our sales history into one string
   stringstream sout;
   sout << retailer << ":\n";
   // continue while there are still customers floating around
   while (!(productionComplete && inventory.empty()))
   {
      // the car to sell
      Car car;

      // it takes time to sell our car
      usleep(rand() % 150000);
      sem_post(&filledSpaces);
      // do we have one to sell
      if (!inventory.empty())
      {

         car = inventory.sellCar();

         sout << "\t" << car << endl;
      }
      sem_post(&emptySpaces);
   }

   // done

   mData->sout = sout.str();
   pthread_exit(0);
} 

/*********************************************
 * GET NUMBER
 * Generic prompt function with error checking
 ********************************************/
int getNumber(const char * prompt, int max)
{
   int value = -1;
   assert(cin.good());       // better not already be in error mode
   assert(prompt != NULL);   // the prompt better be a valid c-string
   assert(max > 0);          // it better be possible for valid data to exist

   // continue prompting until we have valid data
   while (value <= 0 || value > max)
   {
      cout << prompt;
      cin  >> value;

      // if the user typed a non-integer value, reprompt.
      if (cin.fail())
      {
         cin.clear();
         cin.ignore();
         cout << "Error: non-integer value specified\n";
      }

      // if the user typed a valid outside the range, reprompt
      else if (value <= 0 || value > max)
         cout << "Error: value must be between 1 and "
              << max
              << endl;
   }

   return value;
}
