#include "cpu.h"
#include <iostream>
#include <map>

// Constructor implementation
CPU::CPU(INSTRUCTION *current_instruction, char *data_segment): IP(current_instruction), data_segment(data_segment) {}

// Helper functions
bool CPU::isNum(const std::string &str)
{
	return str.find_first_not_of("0123456789") == std::string::npos;
}

bool CPU::isEncapsulatedInBrackets(const std::string &str)
{
	return str.length() >= 2 && str.front() == '[' && str.back() == ']';
}

std::string CPU::removeBrackets(const std::string &str)
{
	if (isEncapsulatedInBrackets(str))
	{
		return str.substr(1, str.length() - 2);
	}
	else
	{
		return str;
	}
}

int CPU::stringToInt(const std::string &str)
{
	return std::stoi(str);
}

void CPU::dump_memory(char* data_segment,int n){
	std::cout <<  std::endl;
	std::cout << "data_segment " << std::endl;
	for(int i = 0; i < n; ++i){
		std::cout << "0x"<< i <<  " " << (int) data_segment[i] << std::endl;
	}
}

void CPU::dump_registers(){
	std::cout <<  std::endl;
	std::cout << "registers " << std::endl;
	std::cout << "ayb -> "<< (int)this->ayb << std::endl;
	std::cout << "ben -> "<< (int)this->ben << std::endl;
	std::cout << "gim -> "<< (int)this->gim << std::endl;
	std::cout << "da -> "<< (int)this->da << std::endl;
	std::cout << "ech -> "<< (int)this->ech << std::endl;
}

// Decoding operations and operands and execute
void CPU::decode_execute(int instruction_count, INSTRUCTION *tmp)
{
	std::map<std::string, int> labels;
	int count = 0;
	int counttmp = 0;
	while (counttmp != instruction_count)
	{
		if (IP->opcode == "label")
		{
			labels[IP->operand1] = counttmp;
		}

		counttmp++;
		IP++;
	}

	IP = tmp;
	while (count != instruction_count)
	{
		if (IP->opcode == "mov")	// mov instruction 
		{ 
			if (!isEncapsulatedInBrackets(IP->operand1) && !isEncapsulatedInBrackets(IP->operand2) && !isNum(IP->operand2))	// mov reg reg  
			{  
				if (IP->operand1 == "ayb")
				{
					if (IP->operand2 == "ben")
					{
						this->ayb = this->ben;
					}
					else if (IP->operand2 == "gim")
					{
						this->ayb = this->gim;
					}
					else if (IP->operand2 == "da")
					{
						this->ayb = this->da;
					}
					else if (IP->operand2 == "ech")
					{
						this->ayb = this->ech;
					}
				}
				else if (IP->operand1 == "ben")
				{
					if (IP->operand2 == "ayb")
					{
						this->ben = this->ayb;
					}
					else if (IP->operand2 == "gim")
					{
						this->ben = this->gim;
					}
					else if (IP->operand2 == "da")
					{
						this->ben = this->da;
					}
					else if (IP->operand2 == "ech")
					{
						this->ben = this->ech;
					}
				}
				else if (IP->operand1 == "gim")
				{
					if (IP->operand2 == "ayb")
					{
						this->gim = this->ayb;
					}
					else if (IP->operand2 == "ben")
					{
						this->gim = this->ben;
					}
					else if (IP->operand2 == "da")
					{
						this->gim = this->da;
					}
					else if (IP->operand2 == "ech")
					{
						this->gim = this->ech;
					}
				}
				else if (IP->operand1 == "da")
				{
					if (IP->operand2 == "ayb")
					{
						this->da = this->ayb;
					}
					else if (IP->operand2 == "ben")
					{
						this->da = this->ben;
					}
					else if (IP->operand2 == "gim")
					{
						this->da = this->gim;
					}
					else if (IP->operand2 == "ech")
					{
						this->da = this->ech;
					}
				}
				else if (IP->operand1 == "ech")
				{
					if (IP->operand2 == "ayb")
					{
						this->ech = this->ayb;
					}
					else if (IP->operand2 == "ben")
					{
						this->ech = this->ben;
					}
					else if (IP->operand2 == "gim")
					{
						this->ech = this->gim;
					}
					else if (IP->operand2 == "da")
					{
						this->ech = this->da;
					}
				}
			}
			else if (!isEncapsulatedInBrackets(IP->operand1) && !isEncapsulatedInBrackets(IP->operand2) && isNum(IP->operand2))	// mov reg literal
			{
				if (IP->operand1 == "ayb")
				{
					this->ayb = stringToInt(IP->operand2);
				}
				else if (IP->operand1 == "ben")
				{
					this->ben = stringToInt(IP->operand2);
				}
				else if (IP->operand1 == "gim")
				{
					this->gim = stringToInt(IP->operand2);
				}
				else if (IP->operand1 == "da")
				{
					this->da = stringToInt(IP->operand2);
				}
				else if (IP->operand1 == "ech")
				{
					this->ech = stringToInt(IP->operand2);
				}
			}
			else if (!isEncapsulatedInBrackets(IP->operand1) && isEncapsulatedInBrackets(IP->operand2) && !isNum(IP->operand2))	// mov reg mem
			{
				if (IP->operand1 == "ayb")
				{
					this->ayb = data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
				else if (IP->operand1 == "ben")
				{
					this->ben = data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
				else if (IP->operand1 == "gim")
				{
					this->gim = data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
				else if (IP->operand1 == "da")
				{
					this->da = data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
				else if (IP->operand1 == "ech")
				{
					this->ech = data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
			}
			else if (isEncapsulatedInBrackets(IP->operand1) && !isEncapsulatedInBrackets(IP->operand2) && !isNum(IP->operand2))	// mov mem reg
			{
				if (IP->operand2 == "ayb")
				{
					data_segment[stringToInt(removeBrackets(IP->operand1))] = this->ayb;
				}
				else if (IP->operand2 == "ben")
				{
					data_segment[stringToInt(removeBrackets(IP->operand1))] = this->ben;
				}
				else if (IP->operand2 == "gim")
				{
					data_segment[stringToInt(removeBrackets(IP->operand1))] = this->gim;
				}
				else if (IP->operand2 == "da")
				{
					data_segment[stringToInt(removeBrackets(IP->operand1))] = this->da;
				}
				else if (IP->operand2 == "ech")
				{
					data_segment[stringToInt(removeBrackets(IP->operand1))] = this->ech;
				}
			}
			else if (isEncapsulatedInBrackets(IP->operand1) && isEncapsulatedInBrackets(IP->operand2) && !isNum(IP->operand2))	// mov mem mem
			{
				data_segment[stringToInt(removeBrackets(IP->operand1))] = data_segment[stringToInt(removeBrackets(IP->operand2))];
			}
			else if (isEncapsulatedInBrackets(IP->operand1) && !isEncapsulatedInBrackets(IP->operand2) && isNum(IP->operand2))	// mov mem literal
			{
				data_segment[stringToInt(removeBrackets(IP->operand1))] = stringToInt(IP->operand2);
			}
		}
		else if (IP->opcode == "add")
		{
			// add instruction
			if (!isEncapsulatedInBrackets(IP->operand1) && isNum(IP->operand2))
			{
			 	// add reg literal
				if (IP->operand1 == "ayb")
				{
					this->ayb += stringToInt(IP->operand2);
				}
				else if (IP->operand1 == "ben")
				{
					this->ben += stringToInt(IP->operand2);
				}
				else if (IP->operand1 == "gim")
				{
					this->gim += stringToInt(IP->operand2);
				}
				else if (IP->operand1 == "da")
				{
					this->da += stringToInt(IP->operand2);
				}
				else if (IP->operand1 == "ech")
				{
					this->ech += stringToInt(IP->operand2);
				}
			}

			if (!isEncapsulatedInBrackets(IP->operand1) && !isEncapsulatedInBrackets(IP->operand2) && !isNum(IP->operand2))	// add reg reg  
			{  
				if (IP->operand1 == "ayb")
				{
					if (IP->operand2 == "ayb")
					{
						this->ayb += this->ayb;
					}
					else if (IP->operand2 == "ben")
					{
						this->ayb += this->ben;
					}
					else if (IP->operand2 == "gim")
					{
						this->ayb += this->gim;
					}
					else if (IP->operand2 == "da")
					{
						this->ayb += this->da;
					}
					else if (IP->operand2 == "ech")
					{
						this->ayb += this->ech;
					}
				}
				else if (IP->operand1 == "ben")
				{
					if (IP->operand2 == "ben")
					{
						this->ben += this->ben;
					}
					else if (IP->operand2 == "ayb")
					{
						this->ben += this->ayb;
					}
					else if (IP->operand2 == "gim")
					{
						this->ben += this->gim;
					}
					else if (IP->operand2 == "da")
					{
						this->ben += this->da;
					}
					else if (IP->operand2 == "ech")
					{
						this->ben += this->ech;
					}
				}
				else if (IP->operand1 == "gim")
				{
					if (IP->operand2 == "gim")
					{
						this->gim += this->gim;
					}
					else if (IP->operand2 == "ayb")
					{
						this->gim += this->ayb;
					}
					else if (IP->operand2 == "ben")
					{
						this->gim += this->ben;
					}
					else if (IP->operand2 == "da")
					{
						this->gim += this->da;
					}
					else if (IP->operand2 == "ech")
					{
						this->gim += this->ech;
					}
				}
				else if (IP->operand1 == "da")
				{
					if (IP->operand2 == "da")
					{
						this->da += this->da;
					}
					else if (IP->operand2 == "ayb")
					{
						this->da += this->ayb;
					}
					else if (IP->operand2 == "ben")
					{
						this->da += this->ben;
					}
					else if (IP->operand2 == "gim")
					{
						this->da += this->gim;
					}
					else if (IP->operand2 == "ech")
					{
						this->da += this->ech;
					}
				}
				else if (IP->operand1 == "ech")
				{
					if (IP->operand2 == "ech")
					{
						this->ech += this->ech;
					}
					else if (IP->operand2 == "ayb")
					{
						this->ech += this->ayb;
					}
					else if (IP->operand2 == "ben")
					{
						this->ech += this->ben;
					}
					else if (IP->operand2 == "gim")
					{
						this->ech += this->gim;
					}
					else if (IP->operand2 == "da")
					{
						this->ech += this->da;
					}
				}
			}
			else if (!isEncapsulatedInBrackets(IP->operand1) && isEncapsulatedInBrackets(IP->operand2) && !isNum(IP->operand2))	// add reg mem
			{
				if (IP->operand1 == "ayb")
				{
					this->ayb += data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
				else if (IP->operand1 == "ben")
				{
					this->ben += data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
				else if (IP->operand1 == "gim")
				{
					this->gim += data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
				else if (IP->operand1 == "da")
				{
					this->da += data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
				else if (IP->operand1 == "ech")
				{
					this->ech += data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
			}
		}
		else if (IP->opcode == "sub")
		{
			// sub instruction
			if (!isEncapsulatedInBrackets(IP->operand1) && isNum(IP->operand2))
			{
			 	// sub reg literal
				if (IP->operand1 == "ayb")
				{
					this->ayb -= stringToInt(IP->operand2);
				}
				else if (IP->operand1 == "ben")
				{
					this->ben -= stringToInt(IP->operand2);
				}
				else if (IP->operand1 == "gim")
				{
					this->gim -= stringToInt(IP->operand2);
				}
				else if (IP->operand1 == "da")
				{
					this->da -= stringToInt(IP->operand2);
				}
				else if (IP->operand1 == "ech")
				{
					this->ech -= stringToInt(IP->operand2);
				}
			}

			if (!isEncapsulatedInBrackets(IP->operand1) && !isEncapsulatedInBrackets(IP->operand2) && !isNum(IP->operand2))	// sub reg reg  
			{  
				if (IP->operand1 == "ayb")
				{
					if (IP->operand2 == "ayb")
					{
						this->ayb -= this->ayb;
					}
					else if (IP->operand2 == "ben")
					{
						this->ayb -= this->ben;
					}
					else if (IP->operand2 == "gim")
					{
						this->ayb -= this->gim;
					}
					else if (IP->operand2 == "da")
					{
						this->ayb -= this->da;
					}
					else if (IP->operand2 == "ech")
					{
						this->ayb -= this->ech;
					}
				}
				else if (IP->operand1 == "ben")
				{
					if (IP->operand2 == "ben")
					{
						this->ben -= this->ben;
					}
					else if (IP->operand2 == "ayb")
					{
						this->ben -= this->ayb;
					}
					else if (IP->operand2 == "gim")
					{
						this->ben -= this->gim;
					}
					else if (IP->operand2 == "da")
					{
						this->ben -= this->da;
					}
					else if (IP->operand2 == "ech")
					{
						this->ben -= this->ech;
					}
				}
				else if (IP->operand1 == "gim")
				{
					if (IP->operand2 == "gim")
					{
						this->gim -= this->gim;
					}
					else if (IP->operand2 == "ayb")
					{
						this->gim -= this->ayb;
					}
					else if (IP->operand2 == "ben")
					{
						this->gim -= this->ben;
					}
					else if (IP->operand2 == "da")
					{
						this->gim -= this->da;
					}
					else if (IP->operand2 == "ech")
					{
						this->gim -= this->ech;
					}
				}
				else if (IP->operand1 == "da")
				{
					if (IP->operand2 == "da")
					{
						this->da -= this->da;
					}
					else if (IP->operand2 == "ayb")
					{
						this->da -= this->ayb;
					}
					else if (IP->operand2 == "ben")
					{
						this->da -= this->ben;
					}
					else if (IP->operand2 == "gim")
					{
						this->da -= this->gim;
					}
					else if (IP->operand2 == "ech")
					{
						this->da -= this->ech;
					}
				}
				else if (IP->operand1 == "ech")
				{
					if (IP->operand2 == "ech")
					{
						this->ech -= this->ech;
					}
					else if (IP->operand2 == "ayb")
					{
						this->ech -= this->ayb;
					}
					else if (IP->operand2 == "ben")
					{
						this->ech -= this->ben;
					}
					else if (IP->operand2 == "gim")
					{
						this->ech -= this->gim;
					}
					else if (IP->operand2 == "da")
					{
						this->ech -= this->da;
					}
				}
			}
			else if (!isEncapsulatedInBrackets(IP->operand1) && isEncapsulatedInBrackets(IP->operand2) && !isNum(IP->operand2))	// sub reg mem
			{
				if (IP->operand1 == "ayb")
				{
					this->ayb -= data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
				else if (IP->operand1 == "ben")
				{
					this->ben -= data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
				else if (IP->operand1 == "gim")
				{
					this->gim -= data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
				else if (IP->operand1 == "da")
				{
					this->da -= data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
				else if (IP->operand1 == "ech")
				{
					this->ech -= data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
			}
		}
		else if (IP->opcode == "mul")
		{
			// mul instruction
			if (!isEncapsulatedInBrackets(IP->operand1) && isNum(IP->operand2))
			{
			 	// mul reg literal
				if (IP->operand1 == "ayb")
				{
					this->ayb *= stringToInt(IP->operand2);
				}
				else if (IP->operand1 == "ben")
				{
					this->ben *= stringToInt(IP->operand2);
				}
				else if (IP->operand1 == "gim")
				{
					this->gim *= stringToInt(IP->operand2);
				}
				else if (IP->operand1 == "da")
				{
					this->da *= stringToInt(IP->operand2);
				}
				else if (IP->operand1 == "ech")
				{
					this->ech *= stringToInt(IP->operand2);
				}
			}

			if (!isEncapsulatedInBrackets(IP->operand1) && !isEncapsulatedInBrackets(IP->operand2) && !isNum(IP->operand2))	// mul reg reg  
			{  
				if (IP->operand1 == "ayb")
				{
					if (IP->operand2 == "ayb")
					{
						this->ayb *= this->ayb;
					}
					else if (IP->operand2 == "ben")
					{
						this->ayb *= this->ben;
					}
					else if (IP->operand2 == "gim")
					{
						this->ayb *= this->gim;
					}
					else if (IP->operand2 == "da")
					{
						this->ayb *= this->da;
					}
					else if (IP->operand2 == "ech")
					{
						this->ayb *= this->ech;
					}
				}
				else if (IP->operand1 == "ben")
				{
					if (IP->operand2 == "ben")
					{
						this->ben *= this->ben;
					}
					else if (IP->operand2 == "ayb")
					{
						this->ben *= this->ayb;
					}
					else if (IP->operand2 == "gim")
					{
						this->ben *= this->gim;
					}
					else if (IP->operand2 == "da")
					{
						this->ben *= this->da;
					}
					else if (IP->operand2 == "ech")
					{
						this->ben *= this->ech;
					}
				}
				else if (IP->operand1 == "gim")
				{
					if (IP->operand2 == "gim")
					{
						this->gim *= this->gim;
					}
					else if (IP->operand2 == "ayb")
					{
						this->gim *= this->ayb;
					}
					else if (IP->operand2 == "ben")
					{
						this->gim *= this->ben;
					}
					else if (IP->operand2 == "da")
					{
						this->gim *= this->da;
					}
					else if (IP->operand2 == "ech")
					{
						this->gim *= this->ech;
					}
				}
				else if (IP->operand1 == "da")
				{
					if (IP->operand2 == "da")
					{
						this->da *= this->da;
					}
					else if (IP->operand2 == "ayb")
					{
						this->da *= this->ayb;
					}
					else if (IP->operand2 == "ben")
					{
						this->da *= this->ben;
					}
					else if (IP->operand2 == "gim")
					{
						this->da *= this->gim;
					}
					else if (IP->operand2 == "ech")
					{
						this->da *= this->ech;
					}
				}
				else if (IP->operand1 == "ech")
				{
					if (IP->operand2 == "ech")
					{
						this->ech *= this->ech;
					}
					else if (IP->operand2 == "ayb")
					{
						this->ech *= this->ayb;
					}
					else if (IP->operand2 == "ben")
					{
						this->ech *= this->ben;
					}
					else if (IP->operand2 == "gim")
					{
						this->ech *= this->gim;
					}
					else if (IP->operand2 == "da")
					{
						this->ech *= this->da;
					}
				}
			}
			else if (!isEncapsulatedInBrackets(IP->operand1) && isEncapsulatedInBrackets(IP->operand2) && !isNum(IP->operand2))	// mul reg mem
			{
				if (IP->operand1 == "ayb")
				{
					this->ayb *= data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
				else if (IP->operand1 == "ben")
				{
					this->ben *= data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
				else if (IP->operand1 == "gim")
				{
					this->gim *= data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
				else if (IP->operand1 == "da")
				{
					this->da *= data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
				else if (IP->operand1 == "ech")
				{
					this->ech *= data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
			}
		}
		else if (IP->opcode == "div")
		{
			// div instruction
			if (!isEncapsulatedInBrackets(IP->operand1) && isNum(IP->operand2))
			{
			 	// div reg literal
				if (IP->operand1 == "ayb")
				{
					this->ayb /= stringToInt(IP->operand2);
				}
				else if (IP->operand1 == "ben")
				{
					this->ben /= stringToInt(IP->operand2);
				}
				else if (IP->operand1 == "gim")
				{
					this->gim /= stringToInt(IP->operand2);
				}
				else if (IP->operand1 == "da")
				{
					this->da /= stringToInt(IP->operand2);
				}
				else if (IP->operand1 == "ech")
				{
					this->ech /= stringToInt(IP->operand2);
				}
			}

			if (!isEncapsulatedInBrackets(IP->operand1) && !isEncapsulatedInBrackets(IP->operand2) && !isNum(IP->operand2))	// div reg reg  
			{  
				if (IP->operand1 == "ayb")
				{
					if (IP->operand2 == "ayb")
					{
						this->ayb /= this->ayb;
					}
					else if (IP->operand2 == "ben")
					{
						this->ayb /= this->ben;
					}
					else if (IP->operand2 == "gim")
					{
						this->ayb /= this->gim;
					}
					else if (IP->operand2 == "da")
					{
						this->ayb /= this->da;
					}
					else if (IP->operand2 == "ech")
					{
						this->ayb /= this->ech;
					}
				}
				else if (IP->operand1 == "ben")
				{
					if (IP->operand2 == "ben")
					{
						this->ben /= this->ben;
					}
					else if (IP->operand2 == "ayb")
					{
						this->ben /= this->ayb;
					}
					else if (IP->operand2 == "gim")
					{
						this->ben /= this->gim;
					}
					else if (IP->operand2 == "da")
					{
						this->ben /= this->da;
					}
					else if (IP->operand2 == "ech")
					{
						this->ben /= this->ech;
					}
				}
				else if (IP->operand1 == "gim")
				{
					if (IP->operand2 == "gim")
					{
						this->gim /= this->gim;
					}
					else if (IP->operand2 == "ayb")
					{
						this->gim /= this->ayb;
					}
					else if (IP->operand2 == "ben")
					{
						this->gim /= this->ben;
					}
					else if (IP->operand2 == "da")
					{
						this->gim /= this->da;
					}
					else if (IP->operand2 == "ech")
					{
						this->gim /= this->ech;
					}
				}
				else if (IP->operand1 == "da")
				{
					if (IP->operand2 == "da")
					{
						this->da /= this->da;
					}
					else if (IP->operand2 == "ayb")
					{
						this->da /= this->ayb;
					}
					else if (IP->operand2 == "ben")
					{
						this->da /= this->ben;
					}
					else if (IP->operand2 == "gim")
					{
						this->da /= this->gim;
					}
					else if (IP->operand2 == "ech")
					{
						this->da /= this->ech;
					}
				}
				else if (IP->operand1 == "ech")
				{
					if (IP->operand2 == "ech")
					{
						this->ech /= this->ech;
					}
					else if (IP->operand2 == "ayb")
					{
						this->ech /= this->ayb;
					}
					else if (IP->operand2 == "ben")
					{
						this->ech /= this->ben;
					}
					else if (IP->operand2 == "gim")
					{
						this->ech /= this->gim;
					}
					else if (IP->operand2 == "da")
					{
						this->ech /= this->da;
					}
				}
			}
			else if (!isEncapsulatedInBrackets(IP->operand1) && isEncapsulatedInBrackets(IP->operand2) && !isNum(IP->operand2))	// div reg mem
			{
				if (IP->operand1 == "ayb")
				{
					this->ayb /= data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
				else if (IP->operand1 == "ben")
				{
					this->ben /= data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
				else if (IP->operand1 == "gim")
				{
					this->gim /= data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
				else if (IP->operand1 == "da")
				{
					this->da /= data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
				else if (IP->operand1 == "ech")
				{
					this->ech /= data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
			}
		}
		else if (IP->opcode == "and")
		{
			// and instruction
			if (!isEncapsulatedInBrackets(IP->operand1) && isNum(IP->operand2))
			{
			 	// and reg literal
				if (IP->operand1 == "ayb")
				{
					this->ayb &= stringToInt(IP->operand2);
				}
				else if (IP->operand1 == "ben")
				{
					this->ben &= stringToInt(IP->operand2);
				}
				else if (IP->operand1 == "gim")
				{
					this->gim &= stringToInt(IP->operand2);
				}
				else if (IP->operand1 == "da")
				{
					this->da &= stringToInt(IP->operand2);
				}
				else if (IP->operand1 == "ech")
				{
					this->ech &= stringToInt(IP->operand2);
				}
			}

			if (!isEncapsulatedInBrackets(IP->operand1) && !isEncapsulatedInBrackets(IP->operand2) && !isNum(IP->operand2))	// and reg reg  
			{  
				if (IP->operand1 == "ayb")
				{
					if (IP->operand2 == "ayb")
					{
						this->ayb &= this->ayb;
					}
					else if (IP->operand2 == "ben")
					{
						this->ayb &= this->ben;
					}
					else if (IP->operand2 == "gim")
					{
						this->ayb &= this->gim;
					}
					else if (IP->operand2 == "da")
					{
						this->ayb &= this->da;
					}
					else if (IP->operand2 == "ech")
					{
						this->ayb &= this->ech;
					}
				}
				else if (IP->operand1 == "ben")
				{
					if (IP->operand2 == "ben")
					{
						this->ben &= this->ben;
					}
					else if (IP->operand2 == "ayb")
					{
						this->ben &= this->ayb;
					}
					else if (IP->operand2 == "gim")
					{
						this->ben &= this->gim;
					}
					else if (IP->operand2 == "da")
					{
						this->ben &= this->da;
					}
					else if (IP->operand2 == "ech")
					{
						this->ben &= this->ech;
					}
				}
				else if (IP->operand1 == "gim")
				{
					if (IP->operand2 == "gim")
					{
						this->gim &= this->gim;
					}
					else if (IP->operand2 == "ayb")
					{
						this->gim &= this->ayb;
					}
					else if (IP->operand2 == "ben")
					{
						this->gim &= this->ben;
					}
					else if (IP->operand2 == "da")
					{
						this->gim &= this->da;
					}
					else if (IP->operand2 == "ech")
					{
						this->gim &= this->ech;
					}
				}
				else if (IP->operand1 == "da")
				{
					if (IP->operand2 == "da")
					{
						this->da &= this->da;
					}
					else if (IP->operand2 == "ayb")
					{
						this->da &= this->ayb;
					}
					else if (IP->operand2 == "ben")
					{
						this->da &= this->ben;
					}
					else if (IP->operand2 == "gim")
					{
						this->da &= this->gim;
					}
					else if (IP->operand2 == "ech")
					{
						this->da &= this->ech;
					}
				}
				else if (IP->operand1 == "ech")
				{
					if (IP->operand2 == "ech")
					{
						this->ech &= this->ech;
					}
					else if (IP->operand2 == "ayb")
					{
						this->ech &= this->ayb;
					}
					else if (IP->operand2 == "ben")
					{
						this->ech &= this->ben;
					}
					else if (IP->operand2 == "gim")
					{
						this->ech &= this->gim;
					}
					else if (IP->operand2 == "da")
					{
						this->ech &= this->da;
					}
				}
			}
			else if (!isEncapsulatedInBrackets(IP->operand1) && isEncapsulatedInBrackets(IP->operand2) && !isNum(IP->operand2))	// and reg mem
			{
				if (IP->operand1 == "ayb")
				{
					this->ayb &= data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
				else if (IP->operand1 == "ben")
				{
					this->ben &= data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
				else if (IP->operand1 == "gim")
				{
					this->gim &= data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
				else if (IP->operand1 == "da")
				{
					this->da &= data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
				else if (IP->operand1 == "ech")
				{
					this->ech &= data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
			}
		}
		else if (IP->opcode == "or")
		{
			// or instruction
			if (!isEncapsulatedInBrackets(IP->operand1) && isNum(IP->operand2))
			{
			 	// or reg literal
				if (IP->operand1 == "ayb")
				{
					this->ayb |= stringToInt(IP->operand2);
				}
				else if (IP->operand1 == "ben")
				{
					this->ben |= stringToInt(IP->operand2);
				}
				else if (IP->operand1 == "gim")
				{
					this->gim |= stringToInt(IP->operand2);
				}
				else if (IP->operand1 == "da")
				{
					this->da |= stringToInt(IP->operand2);
				}
				else if (IP->operand1 == "ech")
				{
					this->ech |= stringToInt(IP->operand2);
				}
			}

			if (!isEncapsulatedInBrackets(IP->operand1) && !isEncapsulatedInBrackets(IP->operand2) && !isNum(IP->operand2))	// or reg reg  
			{  
				if (IP->operand1 == "ayb")
				{
					if (IP->operand2 == "ayb")
					{
						this->ayb |= this->ayb;
					}
					else if (IP->operand2 == "ben")
					{
						this->ayb |= this->ben;
					}
					else if (IP->operand2 == "gim")
					{
						this->ayb |= this->gim;
					}
					else if (IP->operand2 == "da")
					{
						this->ayb |= this->da;
					}
					else if (IP->operand2 == "ech")
					{
						this->ayb |= this->ech;
					}
				}
				else if (IP->operand1 == "ben")
				{
					if (IP->operand2 == "ben")
					{
						this->ben |= this->ben;
					}
					else if (IP->operand2 == "ayb")
					{
						this->ben |= this->ayb;
					}
					else if (IP->operand2 == "gim")
					{
						this->ben |= this->gim;
					}
					else if (IP->operand2 == "da")
					{
						this->ben |= this->da;
					}
					else if (IP->operand2 == "ech")
					{
						this->ben |= this->ech;
					}
				}
				else if (IP->operand1 == "gim")
				{
					if (IP->operand2 == "gim")
					{
						this->gim |= this->gim;
					}
					else if (IP->operand2 == "ayb")
					{
						this->gim |= this->ayb;
					}
					else if (IP->operand2 == "ben")
					{
						this->gim |= this->ben;
					}
					else if (IP->operand2 == "da")
					{
						this->gim |= this->da;
					}
					else if (IP->operand2 == "ech")
					{
						this->gim |= this->ech;
					}
				}
				else if (IP->operand1 == "da")
				{
					if (IP->operand2 == "da")
					{
						this->da |= this->da;
					}
					else if (IP->operand2 == "ayb")
					{
						this->da |= this->ayb;
					}
					else if (IP->operand2 == "ben")
					{
						this->da |= this->ben;
					}
					else if (IP->operand2 == "gim")
					{
						this->da |= this->gim;
					}
					else if (IP->operand2 == "ech")
					{
						this->da |= this->ech;
					}
				}
				else if (IP->operand1 == "ech")
				{
					if (IP->operand2 == "ech")
					{
						this->ech |= this->ech;
					}
					else if (IP->operand2 == "ayb")
					{
						this->ech |= this->ayb;
					}
					else if (IP->operand2 == "ben")
					{
						this->ech |= this->ben;
					}
					else if (IP->operand2 == "gim")
					{
						this->ech |= this->gim;
					}
					else if (IP->operand2 == "da")
					{
						this->ech |= this->da;
					}
				}
			}
			else if (!isEncapsulatedInBrackets(IP->operand1) && isEncapsulatedInBrackets(IP->operand2) && !isNum(IP->operand2))	// or reg mem
			{
				if (IP->operand1 == "ayb")
				{
					this->ayb |= data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
				else if (IP->operand1 == "ben")
				{
					this->ben |= data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
				else if (IP->operand1 == "gim")
				{
					this->gim |= data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
				else if (IP->operand1 == "da")
				{
					this->da |= data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
				else if (IP->operand1 == "ech")
				{
					this->ech |= data_segment[stringToInt(removeBrackets(IP->operand2))];
				}
			}
		}
		else if (IP->opcode == "not")
		{
			// not instruction
			if (!isEncapsulatedInBrackets(IP->operand1) && !isNum(IP->operand1))
			{
			 	// not reg 
				if (IP->operand1 == "ayb")
				{
					this->ayb = ~this->ayb;
				}
				else if (IP->operand1 == "ben")
				{
					this->ben = ~this->ben;
				}
				else if (IP->operand1 == "gim")
				{
					this->gim = ~this->gim;
				}
				else if (IP->operand1 == "da")
				{
					this->da = ~this->da;
				}
				else if (IP->operand1 == "ech")
				{
					this->ech = ~this->ech;
				}
			}
		}
		else if (IP->opcode == "cmp")	// cmp instruction
		{
			if (!isEncapsulatedInBrackets(IP->operand1) && !isNum(IP->operand1) && isNum(IP->operand2))	// cmp reg literal
			{
				if (IP->operand1 == "ayb")
				{
					if (this->ayb > stringToInt(IP->operand2))
					{
						this->za = 1;
					}
					else if (this->ayb < stringToInt(IP->operand2))
					{
						this->za = -1;
					}
					else
					{
						this->za = 0;
					}
				}
				else if (IP->operand1 == "ben")
				{
					if (this->ben > stringToInt(IP->operand2))
					{
						this->za = 1;
					}
					else if (this->ben < stringToInt(IP->operand2))
					{
						this->za = -1;
					}
					else
					{
						this->za = 0;
					}
				}
				else if (IP->operand1 == "gim")
				{
					if (this->gim > stringToInt(IP->operand2))
					{
						this->za = 1;
					}
					else if (this->gim < stringToInt(IP->operand2))
					{
						this->za = -1;
					}
					else
					{
						this->za = 0;
					}
				}
				else if (IP->operand1 == "da")
				{
					if (this->da > stringToInt(IP->operand2))
					{
						this->za = 1;
					}
					else if (this->da < stringToInt(IP->operand2))
					{
						this->za = -1;
					}
					else
					{
						this->za = 0;
					}
				}
				else if (IP->operand1 == "ech")
				{
					if (this->ech > stringToInt(IP->operand2))
					{
						this->za = 1;
					}
					else if (this->ech < stringToInt(IP->operand2))
					{
						this->za = -1;
					}
					else
					{
						this->za = 0;
					}
				}
			}
			else if (!isEncapsulatedInBrackets(IP->operand1) && !isNum(IP->operand1) && !isEncapsulatedInBrackets(IP->operand2) && !isNum(IP->operand2))
			{
				//  cmp reg reg
				if (IP->operand1 == "ayb")
				{
					if (IP->operand2 == "ben")
					{
						if (this->ayb > this->ben)
						{
							this->za = 1;
						}
						else if (this->ayb < this->ben)
						{
							this->za = -1;
						}
						else
						{
							this->za = 0;
						}
					}
					else if (IP->operand2 == "gim")
					{
						if (this->ayb > this->gim)
						{
							this->za = 1;
						}
						else if (this->ayb < this->gim)
						{
							this->za = -1;
						}
						else
						{
							this->za = 0;
						}
					}
					else if (IP->operand2 == "da")
					{
						if (this->ayb > this->da)
						{
							this->za = 1;
						}
						else if (this->ayb < this->da)
						{
							this->za = -1;
						}
						else
						{
							this->za = 0;
						}
					}
					else if (IP->operand2 == "ech")
					{
						if (this->ayb > this->ech)
						{
							this->za = 1;
						}
						else if (this->ayb < this->ech)
						{
							this->za = -1;
						}
						else
						{
							this->za = 0;
						}
					}
				}
				else if (IP->operand1 == "ben")
				{
					if (IP->operand2 == "ayb")
					{
						if (this->ben > this->ayb)
						{
							this->za = 1;
						}
						else if (this->ben < this->ayb)
						{
							this->za = -1;
						}
						else
						{
							this->za = 0;
						}
					}
					else if (IP->operand2 == "gim")
					{
						if (this->ben > this->gim)
						{
							this->za = 1;
						}
						else if (this->ben < this->gim)
						{
							this->za = -1;
						}
						else
						{
							this->za = 0;
						}
					}
					else if (IP->operand2 == "da")
					{
						if (this->ben > this->da)
						{
							this->za = 1;
						}
						else if (this->ben < this->da)
						{
							this->za = -1;
						}
						else
						{
							this->za = 0;
						}
					}
					else if (IP->operand2 == "ech")
					{
						if (this->ben > this->ech)
						{
							this->za = 1;
						}
						else if (this->ben < this->ech)
						{
							this->za = -1;
						}
						else
						{
							this->za = 0;
						}
					}
				}
				else if (IP->operand1 == "gim")
				{
					if (IP->operand2 == "ayb")
					{
						if (this->gim > this->ayb)
						{
							this->za = 1;
						}
						else if (this->gim < this->ayb)
						{
							this->za = -1;
						}
						else
						{
							this->za = 0;
						}
					}
					else if (IP->operand2 == "ben")
					{
						if (this->gim > this->ben)
						{
							this->za = 1;
						}
						else if (this->gim < this->ben)
						{
							this->za = -1;
						}
						else
						{
							this->za = 0;
						}
					}
					else if (IP->operand2 == "da")
					{
						if (this->gim > this->da)
						{
							this->za = 1;
						}
						else if (this->gim < this->da)
						{
							this->za = -1;
						}
						else
						{
							this->za = 0;
						}
					}
					else if (IP->operand2 == "ech")
					{
						if (this->gim > this->ech)
						{
							this->za = 1;
						}
						else if (this->gim < this->ech)
						{
							this->za = -1;
						}
						else
						{
							this->za = 0;
						}
					}
				}
				else if (IP->operand1 == "da")
				{
					if (IP->operand2 == "ayb")
					{
						if (this->da > this->ayb)
						{
							this->za = 1;
						}
						else if (this->da < this->ayb)
						{
							this->za = -1;
						}
						else
						{
							this->za = 0;
						}
					}
					else if (IP->operand2 == "ben")
					{
						if (this->da > this->ben)
						{
							this->za = 1;
						}
						else if (this->da < this->ben)
						{
							this->za = -1;
						}
						else
						{
							this->za = 0;
						}
					}
					else if (IP->operand2 == "gim")
					{
						if (this->da > this->gim)
						{
							this->za = 1;
						}
						else if (this->da < this->gim)
						{
							this->za = -1;
						}
						else
						{
							this->za = 0;
						}
					}
					else if (IP->operand2 == "ech")
					{
						if (this->da > this->ech)
						{
							this->za = 1;
						}
						else if (this->da < this->ech)
						{
							this->za = -1;
						}
						else
						{
							this->za = 0;
						}
					}
				}
				else if (IP->operand1 == "ech")
				{
					if (IP->operand2 == "ayb")
					{
						if (this->ech > this->ayb)
						{
							this->za = 1;
						}
						else if (this->ech < this->ayb)
						{
							this->za = -1;
						}
						else
						{
							this->za = 0;
						}
					}
					else if (IP->operand2 == "ben")
					{
						if (this->ech > this->ben)
						{
							this->za = 1;
						}
						else if (this->ech < this->ben)
						{
							this->za = -1;
						}
						else
						{
							this->za = 0;
						}
					}
					else if (IP->operand2 == "gim")
					{
						if (this->ech > this->gim)
						{
							this->za = 1;
						}
						else if (this->ech < this->gim)
						{
							this->za = -1;
						}
						else
						{
							this->za = 0;
						}
					}
					else if (IP->operand2 == "da")
					{
						if (this->ech > this->da)
						{
							this->za = 1;
						}
						else if (this->ech < this->da)
						{
							this->za = -1;
						}
						else
						{
							this->za = 0;
						}
					}
				}
			}
		}
		else if (IP->opcode == "jmp")
		{
			count = labels[IP->operand1];
			IP = tmp + labels[IP->operand1];
		}
		else if (IP->opcode == "jl")
		{
			if ((int) this->za == -1)
			{
				count = labels[IP->operand1];
				IP = tmp + labels[IP->operand1];
			}
		}
		else if (IP->opcode == "jg")
		{
			if ((int) this->za == 1)
			{
				count = labels[IP->operand1];
				IP = tmp + labels[IP->operand1];
			}
		}
		else if (IP->opcode == "je")
		{
			if ((int) this->za == 0)
			{
				count = labels[IP->operand1];
				IP = tmp + labels[IP->operand1];
			}
		}

		count++;
		IP++;
	}
}