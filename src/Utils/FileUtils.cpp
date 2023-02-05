#include "Utils.h"

using namespace std::filesystem;

std::vector<string> getAllFilesInDirectory(const string& path)
{
    std::vector<string> files;

    for(const auto file : directory_iterator(path)) {
        if(is_directory(file.path())) {
            std::vector<string> tmp = getAllFilesInDirectory(file.path().string() + "/");
            files.insert(std::end(files),std::begin(tmp),std::end(tmp));
        }
        else
            files.push_back(file.path().string());
    }
    return files;
}