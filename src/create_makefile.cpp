#include <fstream>
#include <iostream>
#include <string>
#include <set>

void createMakefile(std::set<std::string>& header_names, std::string exec_name, std::string dir) {
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