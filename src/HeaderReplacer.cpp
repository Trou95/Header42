#include "HeaderReplacer.h"

constexpr const char* DEFAULT_FILE_TYPE = ".c";
constexpr const char* DEFAULT_OUTPUT_PATH = "output";
constexpr char FILE_TYPE_SEPARATOR = ',';

constexpr stFlag flags[] = {
        {"-u", true},
        {"-f", true},
        {"-r", false},
        {"-o", true}
};

HeaderReplacer::HeaderReplacer(int ac, char **av) : args(av + 1, av + ac)
{
    const char* user = getenv("USER");

    setUserName(user ? user : "user");
    setFileTypes(DEFAULT_FILE_TYPE);
    setOutputPath(DEFAULT_OUTPUT_PATH);
    this->is_recursive = false;
    args.erase(std::unique(args.begin(),args.end()),args.end());
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
    for(const auto& file : tmp_files)
        if(isValidFileType(file)) {
            this->sources.insert(file);
        }
}

void HeaderReplacer::initDirectories()
{
    set<string> directories = getDirectoriesFromSources();

    FileService::createDirectory(this->output_path);
    for(const auto& directory : directories) {
        size_t index = directory.find('/');
        if(index == string::npos) {
            FileService::createDirectory(this->output_path + directory);
            continue;
        }
        while((index = directory.find('/',index)) != string::npos)
            FileService::createDirectory(this->output_path + directory.substr(0,index++));
    }
}

void HeaderReplacer::Run()
{
    for(auto file : sources)
    {
        string file_info = FileService::readFile(file);
        Header header = createHeader(file);
        string res;

        res = header.getSign() + "\n\n";
        res += Header::isSign(file_info) ? file_info.substr(Header::_sign_len + 1) : file_info;

        FileService::writeFile(this->output_path + file,res);
    }
}

set<string> HeaderReplacer::getDirectoriesFromSources()
{
    set<string> ret;

    for(const auto& file : this->sources) {
        size_t index = file.find_last_of('.');
        if(index == string::npos)
            continue;
        index = file.find_last_of('/');
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
    return {this->username.c_str(),file_name.c_str(),create_time.c_str(),modify_time.c_str()};
}

int HeaderReplacer::isFlag(const string& flag)
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
        setFileTypes(*(++it));
    else if(*it == "-r")
        this->is_recursive = true;
    else if(*it == "-o")
        setOutputPath(*(++it));
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

bool HeaderReplacer::isValidFileType(const string& path)
{
    const string file_type = FileService::getFileType(path);
    return this->file_types.count(file_type);
}

void HeaderReplacer::setFileTypes(const string& file_types)
{
    vector<string> res = str_split(file_types,FILE_TYPE_SEPARATOR);
    this->file_types.clear();

    for(const auto& file_type : res)
        this->file_types.insert(file_type);
}

void HeaderReplacer::addFileType(const string& file_type)
{
    this->file_types.insert(file_type);
}