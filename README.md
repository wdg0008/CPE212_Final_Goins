# CPE212_Final_Goins
This is the GitHub repository that I am using to store my C++ program for turning ARM32v7 assembly files into machine code files.
This program was written exclusively by Quin Goins for an assignment at The University of Alabama in Huntsville.
This program makes several notable assumptions, including the following:
1. No label is repeated exactly in two different places (C+++ map STL ignores it)
2. A very limited subset of ARM is used (MOV, LDR, STR, ADD, SUB, AND, ORR, LSL, LSR, ASR, ROR, B, BL, CMP)

## Building
Download the source stuff from the .zip, extract it into your directory of choice, and then run the "make" command to build it.
Make comes preinstalled on macOS and almost all major Linux distributions. On Windows, consider using Microsoft's WSL toolsuite or using MSYS2 to bring the toolchain directly to your PC. See the following links:
https://learn.microsoft.com/en-us/windows/wsl/install
https://packages.msys2.org/package/make
## Execution
Run the program as follows: ./assembler <inputFile.s> <outputFile.asm>
The provided "assembler" is an x86 Intel macOS 14 binary, so if your system happens to match that, feel free to try it.
