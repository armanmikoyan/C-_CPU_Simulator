#ifndef CPU_H
#define CPU_H

#include <string>


class INSTRUCTION{
	public:
		std::string opcode;
		std::string operand1;
		std::string operand2;
};

class CPU {
public:
    CPU(INSTRUCTION* current_instruction,char* data_segment);

    // Helper functions
    bool isNum(const std::string& str);
    bool isEncapsulatedInBrackets(const std::string& str);
    std::string removeBrackets(const std::string& str);
    int stringToInt(const std::string& str);
	void dump_memory(char* data_segment,int n);
	void dump_registers();

    // Decoding operations and operands and execute
    void decode_execute(int instruction_count,INSTRUCTION* tmp);


    INSTRUCTION* IP;
	char* data_segment;

    // General purpose registers
    char ayb;
    char ben;
    char gim;
    char da;
    char ech;

    // Flag register for cmp
    char za;
};

#endif // CPU_H
