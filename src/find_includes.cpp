#include <string>
#include <set>

#include "create_makefile.h"
#include "file_searcher.h"

int main (int argc, char** argv) {
    FileSearcher fs(argv[1]);
    
    createMakefile(fs.header_names, argv[2], fs.directory);
    
    return 0;
}