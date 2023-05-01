#pragma once

#include "Utils/Utils.h"
#include "Utils/FileService/FileService.h"
#include "Entities/Header.h"
#include "Utils/Logger/LogService.h"

class HeaderReplacer {

    public:
        HeaderReplacer(int ac, char** av);

        void initFlags();
        void initSourceFiles();
        void initDirectories();
        void Run();

    private:
        vector<string> args;
        bool is_recursive;
        bool header;
        LogService logService;

        string username;
        string output_path;
        string campus;
        unordered_set<string> source_types;
        unordered_set<string> sources;
        unordered_set<string> whitelist_types;
        unordered_set<string> whitelist;


        set<string> getDirectoriesFromSources();

        void copyWhitelist();

        Header createHeader(const string& filepath);
        inline int isFlag(const string& flag) const;
        void setFlag(vector<string>::iterator& it);
        void setUserName(const string& username);
        void setOutputPath(const string& path);
        void setCampus(const string& campus);
        inline bool isValidFileType(const string& path) const;
        void setSourceFileTypes(const string& file_types);
        void addSourceFileType(const string& file_type);
        void setWhiteListTypes(const string& file_types);
        void addWhiteListType(const string& file_type);
        string getPath(string path);

};

