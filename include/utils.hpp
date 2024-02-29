#ifndef UTILS_HPP
# define UTILS_HPP

#include <string>
#include <cctype>
#include <sstream>

namespace utils {
    std::string itoa(const int& n) {
        std::stringstream ss;
        ss << n;
        return ss.str();
    }

    std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \n\r");
        if (first == std::string::npos)
            return "";
        
        size_t last = str.find_last_not_of(" \n\r");
        return str.substr(first, (last - first + 1));
    }
}


#endif // UTILS_HPP