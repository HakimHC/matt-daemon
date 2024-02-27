#include <iostream>
#include <fstream>
#include <cstdlib>

#include <unistd.h>

#include "TintinReporter.hpp"
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

    FileHandler::createDirectory(LOG_DIR_PATH);

    TintinReporter::setLogFile(
        FileHandler::openFileOutput(LOG_FILE_PATH)
    );


    Daemonizer::daemonize();

    TintinReporter::info("Started.");

    system("cat /var/log/matt_daemon/matt_daemon.log");

    while (true) {
        usleep(400);
    }
}