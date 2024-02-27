#include <iostream>
#include <fstream>
#include <cstdlib>

#include <unistd.h>

#include "TintinReporter.hpp"
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
        perror("mkdir");
        std::cerr << "fatal: cannot create directory" << std::endl;
        return 1;
    }


    TintinReporter::setLogFile(
        FileHandler::openFileOutput(LOG_FILE_PATH)
    );
    TintinReporter::info("Started.");

    Daemonizer::daemonize();

    try {
        Server server;
    }
    catch (std::exception &e) {
        TintinReporter::error(e.what());
        TintinReporter::error("Shutting down...");
        // TODO: clean up (unlock files, free memory etc)
        std::exit(1);
    }

    while (true) {
        usleep(400);
    }
}