#include "Utils/Utils.h"
#include "Utils/FileService/FileService.h"

using namespace std;
using std::vector;

constexpr const char* DEFAULT_FILE_TYPE = ".c";
constexpr const char* DEFAULT_OUTPUT_PATH = "output";
constexpr char FILE_TYPE_SEPARATOR = ',';

class HeaderReplacer
{
    public:
        HeaderReplacer(int ac, char** av) : args(av + 1, av + ac) {
            setUserName(getenv("USER"));
            setFileTypes(DEFAULT_FILE_TYPE);
            setOutputPath(DEFAULT_OUTPUT_PATH);
            this->is_recursive = false;
            args.erase(std::unique(args.begin(),args.end()),args.end());
        }

        void initFlags() {
            for(auto it = args.begin(); it != args.end(); it++) {
                if(isFlag(*it)) {
                    if(std::next(it) != args.end())
                        setFlag(it);
                }
                else
                    sources.insert(*it);
            }
        }

        void initSourceFiles() {
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

            for(auto v : sources)
                cout << v << endl;
        }

        bool isFlag(const string& flag) {
            return flag == "-u" || flag == "-f" || flag == "-r" || flag == "-o";
        }

        void setFlag(vector<string>::iterator& it) {
            if(*it == "-u")
                setUserName(*(++it));
            else if(*it == "-f")
                setFileTypes(*(++it));
            else if(*it == "-r")
                this->is_recursive = true;
            else if(*it == "-o")
                setOutputPath(*(++it));
        }

        void setUserName(const string& username) {
            this->username = username;
        }

        void setOutputPath(const string& path) {
            if(path.empty())
                throw std::runtime_error("Output path cannot be empty");
            this->output_path = FileService::getCurrentPath() + ((path[0] != '/') ? "/" + path : path);
        }

        bool isValidFileType(const string& path) {
            const string file_type = FileService::getFileType(path);
            return this->file_types.count(file_type);
        }

        void setFileTypes(const string& file_types) {
            vector<string> res = str_split(file_types,FILE_TYPE_SEPARATOR);
            this->file_types.clear();

            for(const auto& file_type : res)
                this->file_types.insert(file_type);
        }

        void addFileType(const string& file_type) {
            this->file_types.insert(file_type);
        }

    private:
        vector<string> args;
        bool is_recursive;

        string username;
        string output_path;
        unordered_set<string> file_types;
        unordered_set<string> sources;

};


using namespace std;

int getFlagIndex(const char* str)
{
    static std::unordered_set<string> flags = {"-u","-c","-h","-o"};

    auto it = flags.find(string(str));
    if(it != flags.end()) {
        return static_cast<int>((std::distance(flags.begin(),flags.end()) - 1) - std::distance(flags.begin(),it));
    }
    return -1;
}


int main(int ac, char** av)
{
    HeaderReplacer headerReplacer(ac,av);

    headerReplacer.initFlags();
    headerReplacer.initSourceFiles();

    auto res = FileService::getFileLastModifyTime("Makefile");
    cout << time_to_str(res) << endl;

    return 0;
}
