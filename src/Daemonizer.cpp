#include <cstdlib>

#include "Daemonizer.hpp"
#include "TintinReporter.hpp"

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

#include <sstream>

Daemonizer::Daemonizer() {}
Daemonizer::~Daemonizer() {}

Daemonizer::Daemonizer(const Daemonizer& other) {
    *this = other;
}

Daemonizer& Daemonizer::operator=(const Daemonizer&) {
    return *this;
}

int Daemonizer::daemonize() {
    TintinReporter::info("Entering daemon mode.");

    pid_t pid = fork();
    if (pid == -1) throw std::runtime_error(strerror(errno));
    if (pid != 0) std::exit(0);

    if (setsid() == -1) throw std::runtime_error(strerror(errno));

    umask(0);
    chdir("/");
    Daemonizer::_closeAndRedirectFds();

    int newPid = getpid();
    std::stringstream ss;

    ss << newPid;
    std::string log = "started. PID:  " + ss.str();

    TintinReporter::info(log);

    return (0);
}

void Daemonizer::_closeAndRedirectFds() {
    int null_fd = open("/dev/null", O_RDWR);
    const int std_fd[] = { STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO };

    TintinReporter::debug("Closing and redirecting file descriptors.");

    for (int fd = 0; fd < 3; fd++) {
        close(fd);
        dup2(null_fd, std_fd[fd]);
    }
}
