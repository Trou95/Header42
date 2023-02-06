#pragma once

#include "Utils/Utils.h"
#include "Utils/FileService/FileService.h"
#include "Entities/Header.h"

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

        string username;
        string output_path;
        unordered_set<string> file_types;
        unordered_set<string> sources;


        set<string> getDirectoriesFromSources();

        Header createHeader(const string& filepath);
        int isFlag(const string& flag);
        void setFlag(vector<string>::iterator& it);
        void setUserName(const string& username);
        void setOutputPath(const string& path);
        bool isValidFileType(const string& path);
        void setFileTypes(const string& file_types);
        void addFileType(const string& file_type);

};

