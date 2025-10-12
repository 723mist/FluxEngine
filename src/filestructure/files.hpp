#include <filesystem>
#include "string"

class Create {
public:
    void NewFile(std::string file_name = "simple.txt");
    void NewFolder(std::string folder_name = "content");

    void NewFileInPath(std::string  name = "simple.txt", std::string file_path = "");
    void NewFolderInPath(std::string folder_name = "content", std::string folder_path =  "");
};

class Delete {
public:
    void DelFile();
    void DelFolder();
};
