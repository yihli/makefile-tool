#include <regex>
#include <iostream>
#include <string>
#include <set>
#include <fstream>

#include "file_searcher.h"

void FileSearcher::getDirectory(std::string file_name) {
    std::regex directory_pattern("^(.+/)([^/]+)$"); // regex for the directory 
    std::smatch match;
    // std::string directory_name;

    // extracting the directory from the file path
    std::regex_search(file_name, match, directory_pattern);
    directory = match[1];

}

void FileSearcher::getFileName(std::string file_name) {
    std::regex directory_pattern("^(.+/)([^/]+)$"); // regex for the directory 
    std::smatch match;
    // std::string main_file;

    // extracting the directory from the file path
    std::regex_search(file_name, match, directory_pattern);
    main_file = match[2];
    main_file.erase(main_file.size() - 3, 3);
    main_file.append("o");
    header_names.insert(main_file);

    // return main_file;
}

void FileSearcher::findHeaders(std::string file_name, std::set<std::string>& header_names) {
    std::regex pattern("[[:space:]]*#include[[:space:]]*\"(.*)\""); // create a pattern object from regex library
    // std::string directory = getDirectory(file_name);
    std::smatch match; // for capture groups
    std::fstream file;
    std::string line;

    // opens the file from argument for reading
    // std::ios::in specifies reading mode
    file.open(file_name, std::ios::in);
    std::cout << "opened " << file_name << std::endl;

    // std::getline(file, line);
    while (std::getline(file, line)) {
        // error with regex_match because it considers the ENTIRE string
        if (std::regex_search(line, match, pattern)) {

            std::string name(match[1]);
            
            // optimize this
            // changing extension to find the files
            name[name.size() - 1] = 'c';
            name.append("pp");

            // check to see if headers are being repeated. 
            if (file_name.compare(directory + name) == 0) {
                std::cout << "duplicate name found" << std::endl;
                std::cout << directory + name << std::endl;
                continue;
            }

            findHeaders(directory + name, header_names);
            name.erase(name.size() - 3, 3);
            name.append("o");
            header_names.insert(name);
        }
    }

    file.close();
}

