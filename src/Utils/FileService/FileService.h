#pragma once

#include <string>
#include <vector>
#include <filesystem>

class FileService {

    public:
        static std::string getCurrentPath();
        static const std::string getFileType(const std::string& path);
        static bool isDirectory(const std::string& path);
        static void createDirectory(const std::string& path);
        static std::vector<std::string> getAllFilesInDirectory(const std::string& path);



};
