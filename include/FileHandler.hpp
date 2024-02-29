#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#include <string>
#include <fstream>


class FileHandler {
    public:
        static int createDirectory(const std::string&);
        static std::ofstream* openFileOutput(const std::string&);
        static bool fileExists(const std::string&);
        static int createFile(const std::string&);

        static void lock(const std::string&);
        static void unlock();
        static void removeFile(const std::string&);
    private:
        FileHandler();
        ~FileHandler();

        FileHandler(const FileHandler&);
        FileHandler& operator=(const FileHandler&);

        static int      _lockFileFd;
};

#endif