#include <iostream>
#include <fstream>
#include <cstdlib>

#include <unistd.h>

#include "TintinReporter.hpp"
#include "SignalHandler.hpp"
#include "Server.hpp"
#include "Daemonizer.hpp"
#include "FileHandler.hpp"
#include "constants.hpp"


void notRootError() {
    std::cerr << "fatal: must be executed with root permissions." << std::endl;
    std::exit(1);
}

int main() {
    if (geteuid() != 0)
        notRootError();


    if (FileHandler::createDirectory(LOG_DIR_PATH) == -1) {
        std::cerr << "fatal: cannot create directory" << std::endl;
        perror("mkdir");
        return 1;
    }

    #if 1
    TintinReporter::setLogFile(
        FileHandler::openFileOutput(LOG_FILE_PATH)
    );
    #else
    TintinReporter::setLogFile(
        FileHandler::openFileOutput("/dev/stdout")
    );
    #endif


    TintinReporter::info("Started.");


    try {
        TintinReporter::info("Locking matt_daemon.lock file.");
        FileHandler::lock(LOCK_FILE_PATH);
    }
    catch (std::exception& e) {
        std::string errMessage = "matt_daemon.lock is already locked. Shutting down...";
        TintinReporter::error(errMessage);
        std::cerr << errMessage << std::endl;
        delete TintinReporter::getLogFile();
        return 1;
    }

    SignalHandler::sigListen();
    int exitCode = 0;

    try {
        Daemonizer::daemonize();
    } catch (std::exception& e) {
        TintinReporter::error(e.what());
        exitCode = 1;
        goto handle;
    }

    SignalHandler::sigListen();

    try {
        Server server;
        server.run();
    }
    catch (std::exception &e) {
        TintinReporter::error(e.what());
        TintinReporter::error("Shutting down...");
        exitCode =  1;
    }

handle:
    FileHandler::unlock();
    delete TintinReporter::getLogFile();

    return exitCode;
}