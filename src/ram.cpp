#include "ram.h"

RAM::RAM(int n) {
    code_segment_size = n;
    code_segment = new INSTRUCTION[n];
    data_segment = new char[32 - n];
}

RAM::~RAM() {
    delete[] code_segment;
    delete[] data_segment;
}

void RAM::loadInstruction(std::vector<std::vector<std::string> > data) {
    for (int i = 0; i < data.size(); ++i) {
        INSTRUCTION obj;
        code_segment[i] = obj;
        code_segment[i].operand1 = i;
        for (int j = 0; j < data[i].size(); ++j) {
            if (data[i].size() == 3) {
                code_segment[i].opcode = data[i][j];
                code_segment[i].operand1 = data[i][j + 1];
                code_segment[i].operand2 = data[i][j + 2];
                break;
            }
            else if (data[i].size() == 2) {
                code_segment[i].opcode = data[i][j];
                code_segment[i].operand1 = data[i][j + 1];
                code_segment[i].operand2 = "null";
                break;
            }
        }
    }
}
