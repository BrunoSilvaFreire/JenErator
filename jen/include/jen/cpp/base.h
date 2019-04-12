#ifndef JENERATOR_BASE_H
#define JENERATOR_BASE_H

#include <string>

namespace jen {
    class CXXNamed {
    private:
        std::string name;
    public:
        explicit CXXNamed(std::string name);

        const std::string &getName() const;
    };


    class CXXType : public CXXNamed {
    public:
        explicit CXXType(const std::string &name);
    };

}
#endif
