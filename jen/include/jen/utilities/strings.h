#ifndef JENERATOR_STRINGS_H
#define JENERATOR_STRINGS_H

#include <string>
#include <vector>

namespace jen::strings {
    std::string join(const std::vector<std::string> &strings, const std::string &delimiter = ", ");

    bool starts_with(const std::string &str, const std::string &b);
    bool contains(const std::string &str, const std::string &b);
}
#endif
