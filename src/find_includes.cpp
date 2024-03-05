#include <iostream>
#include <string>
#include <fstream>
#include <regex>

int main (int argc, char** argv) {

    std::regex pattern( "[[:space:]]*#include[[:space:]]*\"(.*)\""); // create a pattern object from regex library
    std::smatch match; // for capture groups
    std::fstream file;
    std::string line;

    // file.good() checks if the file exists and can be opened. 
    if (!file.good()) {
        std::cout << "Error opening file." << std::endl;
    }

    // opens the file from argument for reading
    // std::ios::in specifies reading mode
    file.open(argv[1], std::ios::in);

    std::getline(file, line);
    while (std::getline(file, line)) {

        // error with regex_match because it considers the ENTIRE string
        if (std::regex_search(line, match, pattern)) {
            std::cout << match[1] << std::endl; //print out the captured group
        }
    }

    file.close();
    return 0;
}