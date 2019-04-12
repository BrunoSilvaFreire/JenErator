#include <utility>

#ifndef JENERATOR_INVOCATION_H
#define JENERATOR_INVOCATION_H

#include <vector>
#include <jen/cpp/base.h>

namespace jen {
    class CXXParameter : public CXXNamed {
    private:
        CXXType *type;
    public:
        CXXParameter(const std::string &name, CXXType *type) : CXXNamed(name), type(type) {}

        CXXType *getType() const {
            return type;
        }
    };

    class CXXInvocable {
    private:
        std::vector<CXXParameter> parameters;
    public:
        explicit CXXInvocable(std::vector<CXXParameter> parameters) : parameters(std::move(parameters)) {}

        const std::vector<CXXParameter> &getParameters() const {
            return parameters;
        }
    };

}
#endif
