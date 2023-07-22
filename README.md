 
# PICSART ACADEMY

#  C++_CPU_Simulator
 


## Project Description

 Assembly Code Interpreter and Executor

## Program Compilation and Execution

1 step build -> g++ main.cpp ram.cpp cpu.cpp file_reader.cpp -o simulator
2 step run -> ./simulator

## Usage

write assembly code on  "assembly" file

Each instruction and operand should be separated by whitespace

# example

### mov ayb 0
### label l1
### add ayb 1
### cmp ayb 10
### jl l1

## For jump use  " label + label name " 

# Example 

### label l1
### jmp l1


