# Big-integer-arithmetic-project-Data-Structure-course-
This is a C program that performs arithmetic operations on Big integer numbers represented as custom data structures called `INTEGER` that uses linked list to represent big integers and apply operations on them efficiently . The program allows you to read integers from a file, perform addition, subtraction, multiplication, and division operations on them, and store the results in an output file. Additionally, it handles division by zero and displays the results along with the original expressions.

## Table of Contents

- [Features](#features)
- [Prerequisites](#prerequisites)
- [How to Use](#how-to-use)
- [File Structure](#file-structure)

## Features

- Read integers from a file and store them in a linked list.
- Perform addition, subtraction, multiplication, and division operations on integers.
- Handle division by zero gracefully.
- Store the results of arithmetic operations along with the original expressions in an output file.
- User-friendly menu-driven interface.
- Optmized algorithms to do the arithmetic on large numbers . 

## Prerequisites

- This program is written in C and requires a C compiler to build and run.
- Make sure you have a C compiler (e.g., GCC) installed on your system.

## How to Use

1. Clone the repository or download the source code files.

2. Open a terminal and navigate to the directory containing the source code.

3. Compile the code using a C compiler. For example, with GCC, use the following command:

gcc main.c -o integer_arithmetic

4. Run the program: ./integer_arithmetic

5. Follow the on-screen instructions to perform various operations on integers:

- Read input integers from a file.
- Display the list of integers.
- Perform addition, subtraction, multiplication, and division.
- Print results to an output file.
- Exit the program.

## File Structure

The project files are organized as follows:

- `main.c`: The main program file containing the implementation of arithmetic operations and the menu-driven interface.
- `INTEGER.c` and `INTEGER.h`: Files defining the custom `INTEGER` data structure and related functions for arithmetic operations.
- `ExpressionNode.c` and `ExpressionNode.h`: Files defining the `ExpressionNode` data structure and functions for managing expressions.
- `ListOfIntegers.c` and `ListOfIntegers.h`: Files defining the `ListOfIntegers` data structure and functions for managing the list of integers.

