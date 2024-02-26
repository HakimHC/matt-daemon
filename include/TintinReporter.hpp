#include <string>


class TintinReporter {
    public:
        TintinReporter();
        ~TintinReporter();

        TintinReporter(const TintinReporter&);
        TintinReporter& operator=(const TintinReporter&);

        void log(const std::string& logLevel) const;
};