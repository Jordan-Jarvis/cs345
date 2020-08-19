###############################################################
# Program:
#     Lab08, OMP Lab
#     Brother Comeau, CS235
# Author:
#     Jordan Jarvis
# Summary:
#     This program calculates matrix multiplication using 
#     threads
# Time:
#     10 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: lab08.cpp
	g++ -o a.out -fopenmp lab08.cpp 
	tar -czf lab08.tar makefile lab08.cpp

sampleVariableThreads.out: sampleVariableThreads.cpp
	g++ -o sampleVariableThreads.out -fopenmp sampleVariableThreads.cpp

all: a.out sampleVariableThreads.out
	
