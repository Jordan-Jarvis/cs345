###############################################################
# Program:
#     Lab 04, Scheduling Lab
#     Brother Comeau, CS345
# Author:
#     Jordan Jarvis
# Summary:
#     This program shows multiple ways to schedule multiple
#     programs to run.
# Time:
#     <how long did it take to complete this program?>
###############################################################

##############################################################
# The main rule
##############################################################
a.out: lab04.o schedule.o
	g++ -o a.out lab04.o schedule.o
	tar -j -cf lab04.tar makefile *.cpp *.h

##############################################################
# The individual components
##############################################################
lab04.o: lab04.cpp schedule.h 
	g++ -c lab04.cpp

schedule.o: schedule*.h schedule.cpp process.h
	g++ -c schedule.cpp

