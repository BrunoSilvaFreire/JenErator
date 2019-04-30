#include <jen/utilities/strings.h>

namespace jen::strings {

    std::string join(const std::vector<std::string> &strings, const std::string &delimiter) {
        std::string result;
        auto end = strings.size();
        for (int i = 0; i < end; ++i) {
            result += strings[i];
            if (i != end - 1) {
                result += delimiter;
            }
        }
        return result;
    }

    bool starts_with(const std::string &str, const std::string &b) {
        return str.rfind(b, 0) == 0;
    }

    bool contains(const std::string &str, const std::string &b) {
        return str.find(b) != std::string::npos;
    }

}