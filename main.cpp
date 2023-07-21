#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "file_reader.h"
#include <sstream>


class INSTRUCTION{
	public:
		std::string opcode;
		std::string operand1;
		std::string operand2;
};


class RAM {
  public: 
  INSTRUCTION* code_segment;
  char* data_segment;

  RAM(int n) {
    code_segment = new INSTRUCTION[n];
    data_segment = new char[32 - n];
  }

	void loadInstruction(std::vector<std::vector<std::string> > data) {
		for(int i = 0; i < data.size(); ++i) {
		INSTRUCTION obj;
		code_segment[i] = obj;
		code_segment[i].operand1 = i;
		for(int j = 0; j < data[i].size();++j){
			if(data[i].size() == 3){
				code_segment[i].opcode =data[i][j];
				code_segment[i].operand1 = data[i][j+1];
				code_segment[i].operand2 =data[i][j+2];
				break;
				
			}
			else if(data[i].size() == 2){			
				code_segment[i].opcode =data[i][j];
				code_segment[i].operand1 =data[i][j+1];
				break;
			}
		

		}
	
	}
	}
};
class CPU{
	
	public:
		INSTRUCTION* IP;
		char ayb;
		char ben;
		char gim;
		char da;
		char ech;
		char za;

		 CPU(INSTRUCTION* current_instruction){
	 	 IP = current_instruction;
  	}
	
};


int main(){
 std::vector<std::vector<std::string> > data = matrix("assembly");
 
 	RAM ram(data.size());
	ram.loadInstruction(data);
	CPU cpu(ram.code_segment);
	std::cout << cpu.IP->opcode;

		return 0;
}