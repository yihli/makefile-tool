#include <fstream>
#include <iostream>
#include <string>
#include <set>

/*
 * Generates the Makefile template and adds the lines needed to generate the 
 * executable. Makefile is created in the given directory.
 * 
 * @param header_names: the set of header names to include
 * @param exec_name: the name of the executable
 * @param dir: the directory to place the Makefile in
 * 
 */
void createMakefile(std::set<std::string>& header_names, std::string exec_name, std::string dir) {
    // creating Makefile file. overwrites existing Makefile.
    std::ofstream file(dir + "Makefile");

    file << "(CXX)=g++" << '\n';
    file << "(CXXFLAGS)=-Wall" << "\n\n";
    file << "all : " << exec_name << "\n\n";

    file << exec_name << ": ";
    
    // this adds all the associated header names to the Makefile
    for (auto iter = header_names.begin(); iter != header_names.end(); iter++) {
        file << *iter << " ";
    }

    file << "\n\t$(CXX) $^ -o $@" << "\n\n";
    file << "clean: \n";
    file << "\trm -f *.o " << exec_name;

    std::cout << "Makefile created." << std::endl;
    file.close();
}