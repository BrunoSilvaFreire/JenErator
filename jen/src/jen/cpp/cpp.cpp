#include <utility>

#include <utility>


#include <vector>
#include <jen/cpp/cpp.h>

namespace jen {

    CXXComposite::CXXComposite(
            const std::string &name,
            std::vector<CXXField> fields,
            std::vector<CXXMethod> methods
    ) : CXXType(name), fields(std::move(fields)), methods(std::move(methods)) {}

    const std::vector<void *> &CXXTranslationUnit::getElements() const {
        return elements;
    }
}
