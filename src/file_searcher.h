#ifndef FILE_SEARCHER_H
#define FILE_SEARCHER_H

#include <set>
#include <string>

class FileSearcher {
    public:
    void getDirectory(std::string file_name);
    void getFileName(std::string file_name);
    void findHeaders(std::string file_name, std::set<std::string>& header_names);

    // private:
    std::set<std::string> header_names;
    std::string main_file;
    std::string directory;
};

#endif