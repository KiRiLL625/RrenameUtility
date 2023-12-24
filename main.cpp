#include <iostream>
#include <filesystem>
#include <regex>

namespace fs = std::filesystem;

int main(int argc, char** argv){
    if(argc < 4 || argc > 5){
        std::cout << "Usage: " << argv[0] << " <path> [-r] <old_name> <new_name>" << std::endl;
        return -1;
    }
    fs::path p = fs::current_path() / argv[1];
    if(strcmp(argv[2], "-r") == 0){
        std::string old_name = argv[3];
        std::string new_name = argv[4];
        std::regex reg(old_name);
        for(auto& x : fs::recursive_directory_iterator(p)){
            if(std::regex_search(x.path().filename().string(), reg)){
                fs::rename(x.path(), x.path().parent_path() / new_name);
            }
        }
    }
    else{
        std::string old_name = argv[2];
        std::string new_name = argv[3];
        std::regex reg(old_name);
        for(auto& x : fs::directory_iterator(p)){
            if(std::regex_search(x.path().filename().string(), reg)){
                fs::rename(x.path(), x.path().parent_path() / new_name);
            }
        }
    }
    return 0;
}
