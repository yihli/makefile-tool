#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <set>

void find_headers(std::string file_name, std::set<std::string>& header_names) {
    std::regex pattern( "[[:space:]]*#include[[:space:]]*\"(.*)\""); // create a pattern object from regex library
    std::smatch match; // for capture groups
    std::fstream file;
    std::string line;

    // opens the file from argument for reading
    // std::ios::in specifies reading mode
    file.open(file_name, std::ios::in);

    std::getline(file, line);
    while (std::getline(file, line)) {
        // error with regex_match because it considers the ENTIRE string
        if (std::regex_search(line, match, pattern)) {
            std::string name(match[1]);
            std::cout << name << std::endl; //print out the captured group
        }
    }

    file.close();
}

int main (int argc, char** argv) {
    std::set<std::string> header_names;

    find_headers(argv[1], header_names);

    return 0;
}