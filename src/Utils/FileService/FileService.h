#pragma once

#include <cstring>
#include <sys/stat.h>

#include <iostream>
#include <fstream>
#include <memory>
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
        static const std::string getFileName(const std::string& path);
        static const std::string getFileType(const std::string& path);
        static bool isDirectory(const std::string& path);
        static void createDirectory(const std::string& path);
        static std::vector<std::string> getAllFilesInDirectory(const std::string& path);
        static std::string readFile(const std::string& path);
        static void writeFile(const std::string& path,const std::string& str);
        static long long getFileLen(const std::string& path);



};
