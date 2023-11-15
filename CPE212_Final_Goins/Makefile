# CPE 212_Final_Goins makefile for building without Xcode/Visual Studio
# Should require C++ 14 in case I decide to use binary integer representation
# Both macros enable all warnings
CC=g++ -std=c++14 -Wall
# CC=g++ -std=c++14 -Wall -fprofile-arcs -ftest-coverage
# Uncomment above line for testing purposes

assembler: finalFunctions.o main.o
	$(CC) finalFunctions.o main.o  -o assembler

finalFunctions.o: finalFunctions.hpp finalFunctions.cpp
	$(CC) -c finalFunctions.cpp

main.o: finalFunctions.hpp main.cpp
	$(CC) -c main.cpp

clean:
	rm *.o  assembler
