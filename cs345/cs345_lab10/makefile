###############################################################
# Program:
#     Lab 10, Page Replacement Lab
#     Brother Comeau, CS345
# Author:
#     Jordan Jarvis
# Summary:
#     replaces pages in a simulated page environment using a 
#     variety of techniques
# Time:
#     10 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: lab10.o pr.o
	g++ -o a.out lab10.o pr.o
	tar -czf lab10.tar makefile *.cpp *.h

##############################################################
# The individual components
##############################################################
lab10.o: lab10.cpp pr.h
	g++ -c lab10.cpp

pr.o: pr*.h pr.cpp pr.h
	g++ -c pr.cpp

