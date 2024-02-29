#ifndef TINTIN_REPORTER_HPP
#define TINTIN_REPORTER_HPP

#include <string>
#include <fstream>


class TintinReporter {
    public:

        static void debug(const std::string&);
        static void info(const std::string&);
        static void warning(const std::string&);
        static void error(const std::string&);

        static void setLogFile(std::ofstream*);
        static std::ofstream* getLogFile();


    private:
        static const std::string            _getFormattedDateTime();
        static void                         _log(const std::string& message, const std::string& logLevel);
        static std::ofstream*               _logFile;

        TintinReporter();
        TintinReporter& operator=(const TintinReporter&);
        ~TintinReporter();
        TintinReporter(const TintinReporter&);
};

#endif // TINTIN_REPORTER_HPP

