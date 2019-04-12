#include <utility>

#include <jen/cpp/base.h>

namespace jen {
    CXXNamed::CXXNamed(std::string name) : name(std::move(name)) {

    }

    const std::string &CXXNamed::getName() const {
        return name;
    }

    CXXType::CXXType(const std::string &name) : CXXNamed(name) {}
}