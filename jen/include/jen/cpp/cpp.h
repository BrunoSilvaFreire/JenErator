#ifndef JENERATOR_CPP_H
#define JENERATOR_CPP_H

#include <string>
#include <vector>
#include <jen/cpp/members.h>

namespace jen {
    class CXXComposite : public CXXType {
    private:
        std::vector<CXXField> fields;
        std::vector<CXXMethod> methods;
    public:
        CXXComposite(
                const std::string &name,
                std::vector<CXXField> fields,
                std::vector<CXXMethod> methods
        );
    };

    class CXXClass : public CXXComposite {

    };

    class CXXGenericPreprocessor : public CXXNamed {
    private:
        std::string content;
    public:
        CXXGenericPreprocessor(
                const std::string &name,
                std::string content
        );

        const std::string &getContent() const;
    };

    class CXXTranslationUnit {
    private:
        std::vector<CXXElement *> elements;
    public:
        CXXTranslationUnit();

        std::vector<CXXElement *> &getElements();


    };


}
#endif
