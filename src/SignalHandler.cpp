#include "SignalHandler.hpp"
#include "TintinReporter.hpp"
#include "FileHandler.hpp"

#include "constants.hpp"

#include <csignal>
#include <cstdlib>

SignalHandler::SignalHandler() {}
SignalHandler::~SignalHandler() {}

SignalHandler::SignalHandler(const SignalHandler& other) {
    *this = other;
}

SignalHandler& SignalHandler::operator=(const SignalHandler& rhs) {
    (void) rhs;
    return *this;
}

void SignalHandler::handler(int signum) {
    (void) signum;

    TintinReporter::info("Signal recieved.");
    TintinReporter::info("Quitting...");
    FileHandler::unlock();
    FileHandler::removeFile(LOCK_FILE_PATH);
    delete TintinReporter::getLogFile();
    std::exit(0);
}

void SignalHandler::sigListen() {
    for (int sig = 1; sig < NSIG; sig++) {
       if (sig != SIGKILL && sig != SIGSTOP) signal(sig, SignalHandler::handler);
    }
}
