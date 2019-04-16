#ifndef JENERATOR_BASE_H
#define JENERATOR_BASE_H

#include <string>

namespace jen {
    class CXXElement {
    public:
        virtual ~CXXElement() = default;

        virtual std::string toString() const = 0;
    };

    class CXXNamed : public CXXElement {
    protected:
        std::string name;
    public:
        explicit CXXNamed(std::string name);

        CXXNamed() = default;

        const std::string &getName() const;
    };


    class CXXType : public CXXNamed {
    public:
        explicit CXXType(const std::string &name);

        std::string toString() const override;
    };

}
#endif
