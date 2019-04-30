#include <jen/jen.h>
#include <jen/cpp/base.h>

namespace jen {
    template<>
    std::string toString<const jen::CXXElement *>(const jen::CXXElement *value) {
        return value->toString();
    }
}