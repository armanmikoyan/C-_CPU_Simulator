#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "file_reader.h"
#include <sstream>
#include <cctype> 
#include "cpu.h"
#include "ram.h"





int main(){

	// assembly file information
	std::vector<std::vector<std::string> > data = matrix("assembly");
	int instruction_count = data.size();
	int data_count = 32 -  data.size();

	// load fetch decode execute
 	RAM ram(instruction_count);
	ram.loadInstruction(data);
	CPU cpu(ram.code_segment,ram.data_segment);		
	cpu.decode_execute(instruction_count,ram.code_segment);


	// print memory
	cpu.dump_memory(ram.data_segment,data_count);
	cpu.dump_registers();

	return 0;
}