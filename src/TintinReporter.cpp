#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>

#include <sys/stat.h>
#include <sys/types.h>

#include <errno.h>

#include "TintinReporter.hpp"

std::ofstream* TintinReporter::_logFile = NULL;


TintinReporter::TintinReporter() {}

TintinReporter::~TintinReporter() {}

TintinReporter::TintinReporter(const TintinReporter& other) {
    *this = other;
}

TintinReporter& TintinReporter::operator=(const TintinReporter& rhs) {
    (void) rhs;
    return *this;
}

void TintinReporter::setLogFile(std::ofstream* file) {
    TintinReporter::_logFile = file;
}

std::ofstream* TintinReporter::getLogFile() {
    return TintinReporter::_logFile;
}

void TintinReporter::_log(const std::string& message, const std::string& logLevel) {
    *(TintinReporter::_logFile) << TintinReporter::_getFormattedDateTime();
    *(TintinReporter::_logFile) << " [ " << logLevel << " ] - ";
    *(TintinReporter::_logFile) << message;
    
    if (message[message.size() - 1] != '\n')
        *(TintinReporter::_logFile) << std::endl;
}

void TintinReporter::debug(const std::string& message) {
    TintinReporter::_log(message, "DEBUG");
}

void TintinReporter::info(const std::string& message) {
    TintinReporter::_log(message, "INFO");
}

void TintinReporter::warning(const std::string& message) {
    TintinReporter::_log(message, "WARNING");
}

void TintinReporter::error(const std::string& message) {
    TintinReporter::_log(message, "ERROR");
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