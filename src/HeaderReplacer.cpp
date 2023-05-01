#include "HeaderReplacer.h"

constexpr const char* DEFAULT_FILE_TYPE = ".c";
constexpr const char* DEFAULT_OUTPUT_PATH = "output";
constexpr const char* DEFAULT_CAMPUS = "fr";
constexpr const char* DEFAULT_WHITELIST = "Makefile";
constexpr char FILE_TYPE_SEPARATOR = ',';

constexpr stFlag flags[] = {
        {"-u", true},
        {"-f", true},
        {"-r", false},
        {"-o", true},
        {"-h", false},
        {"-l", false},
        {"-c",true},
        {"-w",true},
};

HeaderReplacer::HeaderReplacer(int ac, char **av) : args(av + 1, av + ac)
{
    const char* user = getenv("USER");

    setUserName(user ? user : "user");
    setSourceFileTypes(DEFAULT_FILE_TYPE);
    setWhiteListTypes(DEFAULT_WHITELIST);
    setOutputPath(DEFAULT_OUTPUT_PATH);
    setCampus(DEFAULT_CAMPUS);
    this->is_recursive = false;
    this->header = true;
    args.erase(std::unique(args.begin(),args.end()),args.end());
    this->logService = std::unique_ptr<ILogger>(new Logger());
}

void HeaderReplacer::initFlags()
{
    for(auto it = args.begin(); it != args.end(); it++) {
        int index;

        if((index = isFlag(*it)) != -1) {
            if(!flags[index].arg || std::next(it) != args.end())
                setFlag(it);
        }
        else
            sources.insert(*it);
    }
}

void HeaderReplacer::initSourceFiles()
{
    set<string> tmp_files;

    if(this->is_recursive)
    {
        for(const auto& file : this->sources) {
            if(FileService::isDirectory(file)) {
                vector<string> files = FileService::getAllFilesInDirectory(file);
                tmp_files.insert(files.begin(),files.end());
            }
            else
                tmp_files.insert(file);
        }
    }
    else
    {
        for(const auto& file : this->sources)
            if(!FileService::isDirectory(file))
                tmp_files.insert(file);
    }

    this->sources.clear();
    for(const auto& file : tmp_files) {
         auto tmp = getPath(file);
         if(isValidFileType(tmp)) {
            if(source_types.count(FileService::getFileType(tmp)))
                this->sources.insert(file);
            else
                whitelist.insert(file);
        }
    }
}

void HeaderReplacer::initDirectories()
{
    set<string> directories = getDirectoriesFromSources();

    for(const auto& file : whitelist)
        directories.insert(file);

    
    std::cout << "Directories -------- " << std::endl;

    for(auto file : directories)
        std::cout << file << std::endl;
    
    std::cout << "--------" << std::endl;


    this->logService.logFormat(MESSAGE_INFO, "Creating Directories...");

    FileService::createDirectory(this->output_path);
    for(const auto& directory : directories) {
        size_t index = directory.find('/');
        this->logService.logFormat(MESSAGE_NONE,100, "- Creating: %s", directory.c_str());
        if(index == string::npos) {
            FileService::createDirectory(this->output_path + getPath(directory));
            continue;
        }
        while((index = directory.find('/',index)) != string::npos)
            FileService::createDirectory(this->output_path + getPath(directory.substr(0,index++)));
    }
    this->logService.log("---------------------------------");
}

void HeaderReplacer::Run()
{
    this->logService.logFormat(MESSAGE_INFO, 2000, "Starting.. %d files found",sources.size());

    copyWhitelist();
    for(auto file : sources)
    {
        this->logService.logFormat(MESSAGE_NONE, 100, "- Reading File: %s", file.c_str());
        string res;
        string file_info = FileService::readFile(file);

        if(this->header) {
            Header header = createHeader(file);
            res = header.getSign();
        }
        if(Header::isSign(file_info))
        {
            size_t line_end = Header::_sign_len - 5;
            res += file_info.substr(file_info.find('/',line_end) + 1);
        }
        else
            res += "\n" + file_info;


        this->logService.logFormat(MESSAGE_NONE, 100, "- Writing File: %s",file.c_str());
        FileService::writeFile(this->output_path + getPath(file),res);
    }
    this->logService.logFormat(MESSAGE_INFO, "Finished files located at: %s",this->output_path.c_str());
}

set<string> HeaderReplacer::getDirectoriesFromSources()
{
    set<string> ret;

    for(const auto& file : this->sources) {
        size_t index = file.find_last_of('.');
        if(index == file.npos)
            continue;
        index = file.find_last_of('/');
        if(index == string::npos)
            continue;
        ret.insert(file.substr(0,index) + "/");
    }
    return ret;
}

Header HeaderReplacer::createHeader(const string& filepath)
{
    string res;
    long long time_info;
    string file_name;
    string create_time;
    string modify_time;

    file_name = FileService::getFileName(filepath);
    time_info = FileService::getFileCreateTime(filepath);
    create_time = time_to_str(time_info);
    time_info = FileService::getFileLastModifyTime(filepath);
    modify_time = time_to_str(time_info);
    return {this->username.c_str(),file_name.c_str(),create_time.c_str(),modify_time.c_str(),this->campus.c_str()};
}

void HeaderReplacer::copyWhitelist()
{
    for(auto file : whitelist)
    {
        string file_info = FileService::readFile(file);
        FileService::writeFile(this->output_path + getPath(file),file_info);
    }
}

int HeaderReplacer::isFlag(const string& flag) const
{
    for(long unsigned int i = 0; i < (sizeof(flags) / sizeof(*flags)); i ++)
        if(flags[i].name == flag)
            return static_cast<int>(i);
    return -1;
}

void HeaderReplacer::setFlag(vector<string>::iterator& it)
{
    if(*it == "-u")
        setUserName(*(++it));
    else if(*it == "-f")
        setSourceFileTypes(*(++it));
    else if(*it == "-r")
        this->is_recursive = true;
    else if(*it == "-o")
        setOutputPath(*(++it));
    else if(*it == "-h")
        this->header = false;
    else if(*it == "-l")
        this->logService.disable();
    else if(*it == "-c")
        setCampus(*(++it));
    else if(*it == "-w")
        addWhiteListType(*(++it));
}

void HeaderReplacer::setUserName(const string& username)
{
    this->username = username;
}

void HeaderReplacer::setOutputPath(const string& path)
{
    if(path.empty())
        throw std::runtime_error("Output path cannot be empty");
    this->output_path = FileService::getCurrentPath() + ((path[0] != '/') ? "/" + path : path);
    if(path[path.length() - 1] != '/')
        this->output_path += '/';
}

void HeaderReplacer::setCampus(const string &campus)
{
    this->campus = campus;
}

bool HeaderReplacer::isValidFileType(const string& path) const
{
    const string file_type = FileService::getFileType(path);
    return this->source_types.count(file_type) || this->whitelist_types.count(file_type);
}

void HeaderReplacer::setSourceFileTypes(const string& file_types)
{
    vector<string> res = str_split(file_types,FILE_TYPE_SEPARATOR);
    this->source_types.clear();

    for(const auto& file_type : res)
        this->source_types.insert(file_type);
}

void HeaderReplacer::addSourceFileType(const string& file_type)
{
    this->source_types.insert(file_type);
}

void HeaderReplacer::setWhiteListTypes(const string& file_types)
{
    vector<string> res = str_split(file_types,FILE_TYPE_SEPARATOR);
    this->whitelist_types.clear();

    for(const auto& file_type : res)
        this->whitelist_types.insert(file_type);
}

void HeaderReplacer::addWhiteListType(const string& file_type)
{
    this->whitelist_types.insert(file_type);
}

string HeaderReplacer::getPath(string path)
{

    while(path.find("../") == 0)
        path.erase(0,3);
    return path;
}