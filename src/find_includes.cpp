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

            // changing extension to find the files
            name[name.size() - 1] = 'c';
            name.append("pp");
            find_headers(directory + name, header_names);
            // TODO: change extension to .o 
            name.erase(name.size() - 3, 3);
            name.append("o");
            header_names.insert(name);
        }
    }

    file.close();
}

void create_makefile(std::set<std::string>& header_names, std::string exec_name, std::string dir) {
    // creating Makefile file. overwrites existing Makefile.
    std::ofstream file(dir + "Makefile");

    file << "(CXX)=g++" << '\n';
    file << "(CXXFLAGS)=-Wall" << "\n\n";
    file << "all : " << exec_name << "\n\n";

    file << exec_name << ": ";
    
    for (auto iter = header_names.begin(); iter != header_names.end(); iter++) {
        file << *iter << " ";
    }

    file << "\n\t$(CXX) $^ -o $@" << "\n\n";
    file << "clean: \n";
    file << "\trm -f *.o " << exec_name;

    std::cout << "Makefile created." << std::endl;
    file.close();
}


int main (int argc, char** argv) {
    std::set<std::string> header_names;
    std::string directory = get_directory(argv[1]);

    find_headers(argv[1], header_names);
    
    create_makefile(header_names, argv[2], directory);

    return 0;
}