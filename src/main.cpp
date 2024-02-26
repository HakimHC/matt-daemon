#include <iostream>
#include <fstream>
#include <cstdlib>

#include <unistd.h>

#include "TintinReporter.hpp"

void notRootError() {
    std::cerr << "fatal: must be executed with root permissions." << std::endl;
    std::exit(1);
}

int main() {
    if (geteuid() != 0)
        notRootError();

    TintinReporter logger;
    logger.info("Started.");

    // system("cat /var/log/matt_daemon/matt_daemon.log");
}