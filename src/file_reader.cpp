#include "file_reader.h"
#include <fstream>
#include <sstream>

std::vector<std::vector <std::string> > matrix(const std::string& filename) {
    std::vector<std::vector<std::string> > result;
    std::ifstream file(filename);

    if (!file.is_open()) {
        // Handle file open error if necessary
        return result;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::istringstream iss(line);
        std::string word;
        while (iss >> word) {
            row.push_back(word);
        }
        result.push_back(row);
    }

    file.close();
    return result;
}