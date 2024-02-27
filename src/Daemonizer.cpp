#include <cstdlib>

#include "Daemonizer.hpp"

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>

Daemonizer::Daemonizer() {}
Daemonizer::~Daemonizer() {}

Daemonizer::Daemonizer(const Daemonizer& other) {
    *this = other;
}

Daemonizer& Daemonizer::operator=(const Daemonizer&) {
    return *this;
}

int Daemonizer::daemonize() {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return -1;
    }
    if (pid != 0) std::exit(0);

    if (setsid() == -1) {
        perror("setsid");
        return -1;
    }

    umask(0);
    chdir("/");
    Daemonizer::_closeAndRedirectFds();

    return (0);
}

void Daemonizer::_closeAndRedirectFds() {
    int null_fd = open("/dev/null", O_RDWR);
    const int std_fd[] = { STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO };

    for (int fd = 0; fd < 3; fd++) {
        close(fd);
        dup2(null_fd, std_fd[fd]);
    }
}