#ifndef FILE_SEARCHER_H
#define FILE_SEARCHER_H

#include <set>
#include <string>

class FileSearcher {
    public:
    FileSearcher(std::string file_name);
    void getDirectory(std::string file_name);
    void getFileName(std::string file_name);
    void findHeaderNames(std::string file_name);

    // private:
    std::set<std::string> header_names;
    std::string main_file;
    std::string directory;
};

#endif