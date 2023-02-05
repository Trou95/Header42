#include "FileService.h"

std::string FileService::getCurrentPath()
{
    return std::filesystem::current_path().string();
}

const std::string FileService::getFileType(const std::string &path)
{
    int index = path.find_last_of('.');
    if(index == std::string::npos)
        return path;
    return path.substr(index);
}

bool FileService::isDirectory(const std::string &path)
{
    return std::filesystem::is_directory(path);
}

void FileService::createDirectory(const std::string& path)
{
    std::filesystem::create_directory(path);
}

std::vector<std::string> FileService::getAllFilesInDirectory(const std::string &path)
{
    std::vector<std::string> files;

    for(const auto file : std::filesystem::directory_iterator(path)) {
        if(is_directory(file.path())) {
            std::vector<std::string> tmp = getAllFilesInDirectory(file.path().string() + "/");
            files.insert(std::end(files),std::begin(tmp),std::end(tmp));
        }
        else
            files.push_back(file.path().string());
    }
    return files;
}
