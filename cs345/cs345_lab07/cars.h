/***********************************************************************
 * Component
 *    Cars
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This will deal with the details of working with cars
 *
 *    Note that you must compile this with the -lpthread switch:
 *        g++ -lpthread lab06.cpp
 ************************************************************************/

#ifndef CARS_H
#define CARS_H

#include <iostream>      // for COUT
#include <queue>         // for QUEUE
#include <cassert>       // for ASSERT


/*************************************************
 * CAR
 * A car in the inventory consists of a model and a serial number
 ************************************************/
struct Car
{
   const char * model;
   int serialNumber;
};

/******************************************
 * DISPLAY CAR
 * Display one car in a user-friendly way
 ****************************************/
inline std::ostream & operator << (std::ostream & out, const Car & car)
{
   out << car.model << "(#" << car.serialNumber << ")";
   return out;
}

// the number of cars in the production run across all models
#define NUM_CARS 50

// The major models are the following
const char * models[4] =
{
   "540",
   "570GT",
   "650S Spider",
   "P1"
};
inline int numModels() { return sizeof(models) / sizeof(models[0]); }

// A sampling of the retailers are the following
const char * retailers[9] =
{
   "McLaren Beverly Hills",
   "McLaren Monaco",
   "McLaren Palm Beach",
   "McLaren Philadelphia",
   "McLaren Atlanta",
   "McLaren Rancho Mirage",
   "McLaren Tampa Bay",
   "McLaren Paris",
   "McLaren Birmingham"
};
inline int numRetailers() { return sizeof(retailers) / sizeof(retailers[0]); }

/*************************************************************
 * INVENTORY
 * The cars currently in inventory.
 * This class is _NOT_ thread-safe and should not be made so
 ************************************************************/
class Inventory
{
public:
   // default constructor: no cars
   Inventory() : maxCars(0) {}

   // how many cars were in there?
   int getMax() const { return maxCars; }

   // is the inventory empty?
   bool empty() const { return cars.size() == 0 ? true : false; }
   
   // add a car
   void makeCar(const Car & car)
   {
      cars.push(car);
      maxCars = (cars.size() > maxCars ? cars.size() : maxCars);
   }

   // sell a car
   Car sellCar()
   {
      assert(cars.size() > 0);
      Car car = cars.front();
      cars.pop();
      return car;
   }

private:
   int  maxCars;              // the biggest the inventory has yet been
   std::queue <Car> cars;     // the actual cars in the inventory
};

#endif // CARS_H
