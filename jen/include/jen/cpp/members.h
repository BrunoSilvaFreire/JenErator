#include <utility>

#ifndef JENERATOR_MEMBERS_H
#define JENERATOR_MEMBERS_H

#include <cstdint>
#include <jen/cpp/base.h>
#include <jen/cpp/invocation.h>

namespace jen {
    enum CXXAccessModifier : uint8_t {
        ePrivate,
        eProtected,
        ePublic
    };

    class CXXMember : CXXNamed {
    private:
        CXXAccessModifier accessModifier;
    public:
        CXXMember(
                const std::string &name,
                CXXAccessModifier accessModifier
        ) : CXXNamed(name), accessModifier(accessModifier) {}

        CXXAccessModifier getAccessModifier() const {
            return accessModifier;
        }
    };

    class CXXField {

    };

    class CXXMethod : public CXXMember, public CXXInvocable {
    private:
        std::string returnType;
    public:
        explicit CXXMethod(
                CXXAccessModifier modifier,
                const std::string &name,
                const std::vector<CXXParameter> &parameters,
                std::string returnType
        ) : returnType(std::move(returnType)), CXXMember(name, modifier), CXXInvocable(parameters) {}

        std::string getReturnType() const {
            return returnType;
        }
    };
}
#endif
