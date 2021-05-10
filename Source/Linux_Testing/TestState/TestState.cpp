#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <filesystem>

void PrintInfo(const std::string& path)
{
    struct stat info;

    int ret = stat(path.c_str(), &info);
    std::cout << "ret = " << ret << std::endl;
    if (ret != 0)
        printf("cannot access %s\n", path.c_str());

    if (S_ISDIR(info.st_mode))
        printf("%s is a directory\n", path.c_str());
    else
        printf("%s is no directory\n", path.c_str());

}

bool dirExist(const std::string &path)
{
    bool isExist = false;
    struct  stat info;
    if(stat(path.c_str(), &info) == 0 && S_ISDIR(info.st_mode))
        isExist = true;

    return isExist;
}

// Not finished
void CreateDirectories(std::string& path)
{
    size_t pos = 0;
    std::string dir;
    int mdret;

    if(path[path.size() - 1] != '/'){
        path += '/';
    }

    while ((pos = path.find_first_of('/', pos)) != std::string::npos) {
        dir = path.substr(0, pos++);

        if(dir.size() == 0) continue;
        
        if((mdret = mkdir(dir.c_str(), 0777)) &&
            errno != EEXIST){
                std::cout << "Create directory " << dir << " ERROR! \nmkdir return = " << mdret << std::endl;
        }
    }
    
}

void CheckDirExist(std::string& path)
{
    if(!dirExist(path))
        CreateDirectories(path);
}

void CreateDirectories_Cpp17(const std::string& path)
{
    std::filesystem::path dir(path.c_str());
    if(!std::filesystem::exists(dir)){
        std::filesystem::create_directories(dir);
    }
}

int main(int argc, char** argv)
{
    std::string path = "./foo/Test";
    // CheckDirExist(path);
    CreateDirectories_Cpp17(path);

    path = "/mnt/d/Rorze_Data/";
    PrintInfo(path);
    std::cout << dirExist (path) << std::endl;

    getchar();
    return EXIT_SUCCESS;
}