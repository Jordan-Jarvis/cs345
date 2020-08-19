###############################################################
# Program:
#     Lab 11, Disk Scheduling Lab
#     Brother Comeau, CS345
# Author:
#     Jordan Jarvis
# Summary:
#     This program impliments various disk scheduling 
#     algorithms.
# Time:
#     about 10 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: lab11.o ds.o
	g++ -o a.out lab11.o ds.o
	tar -czf lab11.tar makefile *.cpp *.h

##############################################################
# The individual components
##############################################################
lab11.o: lab11.cpp ds.h
	g++ -c lab11.cpp

ds.o: ds*.h ds.cpp ds.h
	g++ -c ds.cpp

