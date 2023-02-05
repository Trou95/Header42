#pragma once

#include <sys/stat.h>

#include <string>
#include <vector>
#include <filesystem>

#ifdef WIN32
    #define stat _stat
#endif

class FileService {

    public:
        static std::string getCurrentPath();
        static time_t getFileCreateTime(const std::string& path);
        static time_t getFileLastModifyTime(const std::string& path);
        static const std::string getFileType(const std::string& path);
        static bool isDirectory(const std::string& path);
        static void createDirectory(const std::string& path);
        static std::vector<std::string> getAllFilesInDirectory(const std::string& path);



};
