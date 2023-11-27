# CPE 212_Final_Goins makefile for building without Xcode/Visual Studio
# Should require C++ 14 in case I decide to use binary integer representation
# Both macros enable all warnings
CC=g++ -std=c++14 -Wall
# CC=g++ -std=c++14 -Wall -fprofile-arcs -ftest-coverage
# Uncomment above line for testing purposes
# Writing this disgustingly long makefile and debugging it really makes me appreciate mature build systems and using fewer files :(

assembler: main.o finalFunctions.o instruction.o dataInstruction.o dataImmediate.o dataRegister.o dataShifted.o memoryInstruction.o memoryImmediate.o memoryRegister.o branchInstruction.o
	$(CC) main.o finalFunctions.o instruction.o dataInstruction.o dataImmediate.o dataRegister.o dataShifted.o memoryInstruction.o memoryImmediate.o memoryRegister.o branchInstruction.o -o assembler

main.o: finalFunctions.hpp instruction.hpp dataInstruction.hpp dataImmediate.hpp dataRegister.hpp dataShifted.hpp memoryInstruction.hpp memoryImmediate.hpp memoryRegister.hpp branchInstruction.hpp main.cpp
	$(CC) -c main.cpp

finalFunctions.o: finalFunctions.hpp finalFunctions.cpp
	$(CC) -c finalFunctions.cpp
	
instruction.o: finalFunctions.hpp instruction.hpp instruction.cpp
	$(CC) -c instruction.cpp
	
dataInstruction.o: finalFunctions.hpp instruction.hpp dataInstruction.hpp dataInstruction.cpp
	$(CC) -c dataInstruction.cpp

dataImmediate.o: finalFunctions.hpp instruction.hpp dataInstruction.hpp dataImmediate.hpp dataImmediate.cpp
	$(CC) -c dataImmediate.cpp

dataRegister.o: finalFunctions.hpp instruction.hpp dataInstruction.hpp dataRegister.hpp dataImmediate.cpp
	$(CC) -c dataRegister.cpp

dataShifted.o: finalFunctions.hpp instruction.hpp dataInstruction.hpp dataShifted.hpp dataShifted.cpp
	$(CC) -c dataShifted.cpp

memoryInstruction.o: finalFunctions.hpp instruction.hpp memoryInstruction.hpp memoryInstruction.cpp
	$(CC) -c memoryInstruction.cpp

memoryImmediate.o: finalFunctions.hpp instruction.hpp memoryInstruction.hpp memoryImmediate.hpp memoryImmediate.cpp
	$(CC) -c memoryImmediate.cpp

memoryRegister.o: finalFunctions.hpp instruction.hpp memoryInstruction.hpp memoryRegister.hpp memoryRegister.cpp
	$(CC) -c memoryRegister.cpp

branchInstruction.o: finalFunctions.hpp instruction.hpp branchInstruction.hpp branchInstruction.cpp
	$(CC) -c branchInstruction.cpp

clean:
	rm *.o  assembler
