#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <set>

std::string get_directory(std::string file_name) {
    std::regex directory_pattern("^(.+/)([^/]+)$"); // regex for the directory 
    std::smatch match;
    std::string directory_name;

    // extracting the directory from the file path
    std::regex_search(file_name, match, directory_pattern);
    directory_name = match[1];
    std::cout << directory_name << '\n';

    return directory_name;
}

void find_headers(std::string file_name, std::set<std::string>& header_names) {
    std::regex pattern("[[:space:]]*#include[[:space:]]*\"(.*)\""); // create a pattern object from regex library
    std::string directory = get_directory(file_name);
    // add f_name
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
            name[name.size() - 1] = 'c';
            name.append("pp");

            // std::cout << "adding " << name << " to set " << std::endl; //print out the captured group

            header_names.insert(name);

            find_headers(directory + name, header_names);

        }
    }

    file.close();
}

void create_makefile() {
    // creating Makefile file. overwrites existing Makefile.
    std::ofstream file("Makefile");

    file << "(CXX)=g++" << '\n';
    file << "(CXXFLAGS)=-Wall" << "\n\n";
    file << "all : " << '\n';
    
    std::cout << "Makefile created." << std::endl;
    file.close();
}


int main (int argc, char** argv) {
    std::set<std::string> header_names;

    find_headers(argv[1], header_names);

    for (auto iter = header_names.begin(); iter != header_names.end(); iter++) {
        std::cout << *iter << '\n';
    }

    create_makefile();

    return 0;
}