#include "FileHandler.hpp"
#include "TintinReporter.hpp"

#include <sys/stat.h>
#include <sys/file.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include <exception>

int FileHandler::_lockFileFd = -1;

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

void FileHandler::lock(const std::string& lockFile) {
    FileHandler::_lockFileFd = open(lockFile.c_str(), O_RDWR | O_CREAT);

    if (flock(FileHandler::_lockFileFd, LOCK_EX | LOCK_NB) < 0)
        throw std::runtime_error("File is already locked.");
}

void FileHandler::unlock() {
    flock(FileHandler::_lockFileFd, LOCK_UN);
    close(FileHandler::_lockFileFd);
}

void FileHandler::removeFile(const std::string& filePath) {
    if (remove(filePath.c_str()) == -1)
        TintinReporter::warning("remove() failed...");
}
