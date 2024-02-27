#include "FileHandler.hpp"

#include <sys/stat.h>
#include <errno.h>

FileHandler::FileHandler() {}
FileHandler::~FileHandler() {}

FileHandler::FileHandler(const FileHandler& other) {
    *this = other;
}

FileHandler& FileHandler::operator=(const FileHandler& rhs) {
    (void) rhs;
    return *this;
}

int FileHandler::createDirectory(const std::string& path) {
    int ret = mkdir(path.c_str(), 0777);
    if (ret == -1 && errno == EEXIST) return 0;
    return ret;
}

int FileHandler::createFile(const std::string& path) {
    std::ofstream file(path.c_str());
    int ret = 0;

    if (!file.good()) ret = 1;
    file.close();
    return ret;
}

std::ofstream* FileHandler::openFileOutput(const std::string& path) {
    std::ofstream* file = new std::ofstream(path.c_str(), std::ios::app);

    if (!file->good()) {
        delete file;
        return NULL;
    }
    return file;
}

bool FileHandler::fileExists(const std::string& path) {
    std::ifstream file(path.c_str());
    bool ret = true;

    if (!file.good()) ret = false;
    file.close();
    return ret;
}