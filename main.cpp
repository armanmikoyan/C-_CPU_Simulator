#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "file_reader.h"
#include <sstream>
#include <cctype> 


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
				code_segment[i].operand2 = "null";
				break;
			}
		

		}
	
	}
	}
};
class CPU{
	
	public:
		INSTRUCTION* IP;

		//general purpos registers
		char ayb;
		char ben;
		char gim;
		char da;
		char ech;

		// flag register
		char za;


		 CPU(INSTRUCTION* current_instruction){
	 	 IP = current_instruction;
  	}

	// helper funtions
	bool isNum(const std::string& str) {
		return str.find_first_not_of("0123456789") == std::string::npos;
	}


		bool isEncapsulatedInBrackets(const std::string& str) {
		if (str.length() >= 2 && str.front() == '[' && str.back() == ']') {
			return true;
		} else {
			return false;
			}
		}

		std::string removeBrackets(const std::string& str) {
			if (str.length() >= 2 && str.front() == '[' && str.back() == ']') {
				return str.substr(1, str.length() - 2);
			} else {
				return str;
			}
		}
		int stringToInt(const std::string& str) {
    		return std::stoi(str);
		}

		// decoding operations and operands and execute
	  void decode_execute(){
		  
		if( IP->opcode == "mov"){
				if(!isEncapsulatedInBrackets(IP->operand1) && !isEncapsulatedInBrackets(IP->operand2) &&  !isNum(IP->operand2)){    // if  operand1  is register and operand2 is register
						if(IP->operand1 == "ayb"){
						
							if(IP->operand2 == "ben"){
									this->ayb = this->ben;
							}
							else if(IP->operand2 == "gim"){
									this->ayb =this->gim;
							}
							else if(IP->operand2 == "da"){
									this->ayb =this->da;
							}
							else if(IP->operand2 == "ech"){
									this->ayb =this->ech;
							}
						}
						else if(IP->operand1 == "ben"){
						
							 if(IP->operand2 == "ayb"){
									this->ben = this->ayb;
							}
							else if(IP->operand2 == "gim"){
									this->ben =this->gim;
							}
							else if(IP->operand2 == "da"){
									this->ben = this->da;
							}
							else if(IP->operand2 == "ech"){
									this->ben =this->ech;
							}
						}
						else if(IP->operand1 == "gim"){
						
							 if(IP->operand2 == "ayb"){
									this->gim = this->ayb;
							}
							else if(IP->operand2 == "ben"){
									this->gim =this->ben;
							}
							else if(IP->operand2 == "da"){
									this->gim = this->da;
							}
							else if(IP->operand2 == "ech"){
									this->gim =this->ech;
							}
						}
						else if(IP->operand1 == "da"){
						
							if(IP->operand2 == "ayb"){
									this->da = this->ayb;
							}
							else if(IP->operand2 == "ben"){
									this->da =this->ben;
							}
							else if(IP->operand2 == "gim"){
									this->da = this->gim;
							}
							else if(IP->operand2 == "ech"){
									this->da =this->ech;
							}
						}
						else if(IP->operand1 == "ech"){
						
							if(IP->operand2 == "ayb"){
									this->ech = this->ayb;
							}
							else if(IP->operand2 == "ben"){
									this->ech =this->ben;
							}
							else if(IP->operand2 == "gim"){
									this->ech = this->gim;
							}
							else if(IP->operand2 == "da"){
									this->ech =this->da;
							}
						}
				}
		  }
	  }

	
	
};


int main(){
 std::vector<std::vector<std::string> > data = matrix("assembly");
 
 	RAM ram(data.size());
	ram.loadInstruction(data);
	CPU cpu(ram.code_segment);
		cpu.ech = 17;
		
		
	cpu.decode_execute();

	std::cout << (int)cpu.da;

		return 0;
}