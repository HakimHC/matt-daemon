#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>

#include <sys/stat.h>
#include <sys/types.h>

#include <errno.h>

#include "TintinReporter.hpp"

#define LOG_DIR_PATH "/var/log/matt_daemon/"
#define LOG_FILE_PATH "/var/log/matt_daemon/matt_daemon.log"

TintinReporter::TintinReporter() {
    mkdir(LOG_DIR_PATH, 0777);

    this->_logFile = new std::ofstream(LOG_FILE_PATH, std::ios::app);
}
TintinReporter::~TintinReporter() {}

TintinReporter::TintinReporter(const TintinReporter& other) {
    *this = other;
}

TintinReporter& TintinReporter::operator=(const TintinReporter& rhs) {
    if (this != &rhs) {;}
    return *this;
}

void TintinReporter::_log(const std::string& message, const std::string& logLevel) const {
    *(this->_logFile) << TintinReporter::_getFormattedDateTime();
    *(this->_logFile) << " [ " << logLevel << " ] - ";
    *(this->_logFile) << message << std::endl;
}

void TintinReporter::debug(const std::string& message) const {
    this->_log(message, "DEBUG");
}

void TintinReporter::info(const std::string& message) const {
    this->_log(message, "INFO");
}

void TintinReporter::warning(const std::string& message) const {
    this->_log(message, "WARNING");
}

void TintinReporter::error(const std::string& message) const {
    this->_log(message, "ERROR");
}

const std::string TintinReporter::_getFormattedDateTime() {
    std::time_t currentTime = std::time(NULL);
    struct tm *timeInfo = std::localtime(&currentTime);

    std::stringstream dateTimeStream;
    dateTimeStream << '[';
    dateTimeStream << std::setfill('0') << std::setw(2) << (timeInfo->tm_mon + 1) << '/';
    dateTimeStream << std::setfill('0') << std::setw(2) << timeInfo->tm_mday << '/';
    dateTimeStream << (timeInfo->tm_year + 1900) << '-';
    dateTimeStream << std::setfill('0') << std::setw(2) << timeInfo->tm_hour << ':';
    dateTimeStream << std::setfill('0') << std::setw(2) << timeInfo->tm_min << ':';
    dateTimeStream << std::setfill('0') << std::setw(2) << timeInfo->tm_sec;
    dateTimeStream << ']';

    return dateTimeStream.str();
}