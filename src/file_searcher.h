#ifndef FILE_SEARCHER_H
#define FILE_SEARCHER_H

#include <set>
#include <string>

class FileSearcher {
    public:
    std::string getDirectory(std::string file_name);
    std::string getFileName(std::string file_name);
    void findHeaders(std::string file_name, std::set<std::string>& header_names);

    private:
    // std::set<std::string> header_names;
};

#endif