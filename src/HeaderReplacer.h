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
        unordered_set<string> file_types;
        unordered_set<string> sources;


        set<string> getDirectoriesFromSources();

        Header createHeader(const string& filepath);
        inline int isFlag(const string& flag) const;
        void setFlag(vector<string>::iterator& it);
        void setUserName(const string& username);
        void setOutputPath(const string& path);
        inline bool isValidFileType(const string& path) const;
        void setFileTypes(const string& file_types);
        void addFileType(const string& file_type);

};

