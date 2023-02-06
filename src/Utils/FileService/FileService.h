#pragma once

#include <cstring>
#include <sys/stat.h>

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <filesystem>


#ifdef statx
        #define  _POSIX_C_SOURCE 200809L
        #include <dirent.h>
        int dirfd(DIR *dirp);
#elif defined(WIN32)
        #include <windows.h>
        #include <io.h>
        #include <fileapi.h>
        #include <timezoneapi.h>
        #define WINDOWS_TICK 10000000
        #define SEC_TO_UNIX_EPOCH 11644473600LL
#elif defined(HAVE_ST_BIRTHTIME)
        #define birthtime(x) x.st_birthtime
#else
         #define birthtime(x) x.st_ctime
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

        #ifdef WIN32
            static time_t fileTimeToPosix(FILETIME ft);
        #endif

};
