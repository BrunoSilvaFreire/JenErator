#include <jen/cpp/cpp.h>

#ifndef JENERATOR_PREPROCESSORS_H
#define JENERATOR_PREPROCESSORS_H

namespace jen {
    class CXXInclude : public CXXNamed {
    public:
        enum Type {
            eBrackets,
            eQuotes
        };
    private:
        Type includeType;
        CXXTranslationUnit translationUnit;
    public:
        CXXInclude() = default;

        CXXInclude(
                const std::string &name,
                Type includeType,
                CXXTranslationUnit translationUnit
        );

        Type getIncludeType() const;

        CXXTranslationUnit &getTranslationUnit();

        std::string toString() const override;
    };

    class CXXMacroDefinition : public CXXNamed {
    public:
        explicit CXXMacroDefinition(const std::string &name);
    };

    class CXXMacroConstantDefinition : public CXXMacroDefinition {
    private:
        std::string value;
    public:
        CXXMacroConstantDefinition(const std::string &name, const std::string &value);

        std::string toString() const override;
    };

    class CXXMacroFunctionDefinition : public CXXMacroDefinition {
    private:
        std::vector<std::string> parameters;
    public:
        CXXMacroFunctionDefinition(
                const std::string &name,
                std::vector<std::string> parameters
        );

        const std::vector<std::string> &getParameters() const;

        bool hasVarargs() const;

        std::string toString() const override;
    };
}
#endif //JENERATOR_PREPROCESSORS_H
