#ifndef TINTIN_REPORTER_HPP
#define TINTIN_REPORTER_HPP

#include <string>
#include <fstream>


class TintinReporter {
    public:
        TintinReporter(std::ofstream*);
        ~TintinReporter();

        TintinReporter(const TintinReporter&);
        TintinReporter& operator=(const TintinReporter&);

        void debug(const std::string&) const;
        void info(const std::string&) const;
        void warning(const std::string&) const;
        void error(const std::string&) const;

        void setLogFile(std::ofstream*);


    private:
        TintinReporter();
        static const std::string    _getFormattedDateTime();
        void                        _log(const std::string& message, const std::string& logLevel) const;
        std::ofstream*              _logFile;
};

#endif // TINTIN_REPORTER_HPP