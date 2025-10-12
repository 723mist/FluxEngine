#include "files.hpp"
#include "ostream"
#include "fstream"

namespace fs = std::filesystem;

void Create::NewFile(std::string file_name) {
    std::ofstream file(file_name);
}

void Create::NewFolder(std::string folder_name) {
    fs::create_directory(folder_name);
}

void Create::NewFolderInPath(std::string folder_name, std::string folder_path) {
    std::string folder_name_and_path = folder_path + folder_name;
    fs::create_directory(folder_name_and_path);
}

void Create::NewFileInPath(std::string  name, std::string file_path) {
    std::string file_name_and_path = file_path + name;
    std::ofstream file(file_name_and_path);
}
