###############################################################
# Program:
#     Lab 06, Producer & Consumer Lab
#     Brother Comeau, CS345
# Author:
#     Jordan Jarvis
# Summary:
#     This program uses threading to produce and sell cars
# Time:
#     about 10 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: lab06.cpp cars.h
	g++ -o a.out lab06.cpp -lpthread
	tar -czf lab06.tar makefile lab06.cpp cars.h

sampleMutex.out: sampleMutex.cpp
	g++ -o sampleMutex.out -lpthread sampleMutex.cpp

sampleBinarySem.out: sampleBinarySem.cpp
	g++ -o sampleBinarySem.out -lpthread sampleBinarySem.cpp

sampleCountSem.out: sampleCountSem.cpp
	g++ -o sampleCountSem.out -lpthread sampleCountSem.cpp

all: a.out sampleMutex.out sampleBinarySem.out sampleCountSem.out
	
