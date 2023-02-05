#include "FileService.h"

std::string FileService::getCurrentPath()
{
    return std::filesystem::current_path().string();
}

time_t FileService::getFileCreateTime(const std::string &path)
{
    struct stat tmp;
    time_t res;

    if(stat(path.c_str(),&tmp) == 0)
        res = tmp.st_ctime;
    return res;
}

time_t FileService::getFileLastModifyTime(const std::string& path)
{
    auto res = std::filesystem::last_write_time(path);
    auto ret = std::chrono::time_point_cast<std::chrono::system_clock::duration>(res - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
    return std::chrono::system_clock::to_time_t(ret);
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
