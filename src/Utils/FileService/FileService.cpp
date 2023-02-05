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

const std::string FileService::getFileName(const std::string &path)
{
    size_t index = path.find_last_of('/');
    return index != std::string::npos ? path.substr(index + 1) : path;
}

const std::string FileService::getFileType(const std::string &path)
{
    size_t index = path.find_last_of('.');
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
    std::cout << "Create " << path << std::endl;
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

std::string FileService::readFile(const std::string &path)
{
    std::ifstream file;
    std::string res;
    long long file_size;

    file.exceptions(std::ios::badbit | std::ios::failbit);

    try {
        file_size = getFileLen(path);
        file.open(path);
        char* buffer = new char[file_size + 1];
        std::unique_ptr<char[]> ptr(buffer);
        file.read(buffer,file_size);
        buffer[file_size] = 0;
        res = buffer;
    }
    catch(std::ios_base::failure& e) {
        std::cerr << std::strerror(errno) << " " << path << std::endl;
    }
    file.close();
    return res;
}

void FileService::writeFile(const std::string &path, const std::string& str)
{
    std::ofstream file;

    file.exceptions(std::ios_base::badbit | std::ios::failbit);

    try {
        file.open(path, std::ios::out | std::ios::trunc);
        file.write(str.c_str(),str.length());
    }
    catch(std::ios_base::failure& e) {
        std::cerr << std::strerror(errno) << " " << path << std::endl;
    }
    file.close();
}

long long FileService::getFileLen(const std::string &path)
{
    long long res;

    try {
        std::ifstream file(path, std::ifstream::ate | std::ifstream::binary);
        res = file.tellg();
    }
    catch(std::ios_base::failure& e) {
        std::cerr << std::strerror(errno) << " " << path << std::endl;
    }
    return res;
}
