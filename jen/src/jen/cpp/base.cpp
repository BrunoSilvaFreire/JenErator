#include <utility>

#include <jen/cpp/base.h>

namespace jen {
    CXXNamed::CXXNamed(std::string name) : name(std::move(name)) {

    }

    const std::string &CXXNamed::getName() const {
        return name;
    }

    CXXType::CXXType(const std::string &name) : CXXNamed(name) {}

    std::string CXXType::toString() const {
        std::string str = "CXXType(";
        str += name;
        str += ')';
        return str;
    }
}