#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <set>

#include "create_makefile.h"
#include "file_searcher.h"

int main (int argc, char** argv) {
    FileSearcher fs;
    fs.getDirectory(argv[1]);
    fs.getFileName(argv[1]);

    fs.header_names.insert(fs.main_file);
    fs.findHeaders(argv[1], fs.header_names);
    
    createMakefile(fs.header_names, argv[2], fs.directory);

    return 0;
}