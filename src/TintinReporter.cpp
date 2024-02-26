#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>

#include "TintinReporter.hpp"

TintinReporter::TintinReporter() {}
TintinReporter::~TintinReporter() {}

TintinReporter::TintinReporter(const TintinReporter& other) {
    *this = other;
}

TintinReporter& TintinReporter::operator=(const TintinReporter& rhs) {
    if (this != &rhs) {;}
    return *this;
}

void TintinReporter::log(const std::string& message, const std::string& logLevel) const {
    std::cout << TintinReporter::_getFormattedDateTime();
    std::cout << " [ " << logLevel << " ] - ";
    std::cout << message << std::endl;
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