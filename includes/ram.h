#ifndef RAM_H
#define RAM_H

#include <vector>
#include <string>

#include "cpu.h"

class RAM {
public: 
    INSTRUCTION* code_segment;
    char* data_segment;

    RAM(int n);
    ~RAM(); // Destructor to free memory

    void loadInstruction(std::vector<std::vector<std::string> > data);

    int code_segment_size;
};

#endif // RAM_H
