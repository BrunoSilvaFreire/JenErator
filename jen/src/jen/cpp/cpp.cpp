#include <utility>

#include <utility>

#include <utility>
#include <vector>
#include <jen/cpp/cpp.h>
#include <jen/cpp/preprocessors.h>
#include <jen/utilities/strings.h>

namespace jen {

CXXComposite::CXXComposite(
    const std::string &name,
    std::vector<CXXField> fields,
    std::vector<CXXMethod> methods
) : CXXType(name), fields(std::move(fields)), methods(std::move(methods)) {}

CXXGenericPreprocessor::CXXGenericPreprocessor(const std::string &name, std::string content) : CXXNamed(
    name), content(std::move(content)) {}

const std::string &CXXGenericPreprocessor::getContent() const {
  return content;
}

CXXInclude::Type CXXInclude::getIncludeType() const {
  return includeType;
}

CXXTranslationUnit &CXXInclude::getTranslationUnit() {
  return translationUnit;
}

CXXInclude::CXXInclude(
    const std::string &name,
    CXXInclude::Type includeType,
    CXXTranslationUnit translationUnit
) : CXXNamed(name), includeType(includeType), translationUnit(std::move(translationUnit)) {}

inline std::string CXXInclude::toString() const {
  std::string str = "CXXInclude(";
  switch (includeType) {
    case Type::eQuotes:str += '"';
      break;
    case Type::eBrackets:str += '<';
      break;
  }
  str += name;
  switch (includeType) {
    case Type::eQuotes:str += '"';
      break;
    case Type::eBrackets:str += '>';
      break;
  }
  str += ')';
  return str;
}

std::vector<CXXElement *> &CXXTranslationUnit::getElements() {
  return elements;
}

CXXTranslationUnit::CXXTranslationUnit() : elements() {}

const std::vector<std::string> &CXXMacroFunctionDefinition::getParameters() const {
  return parameters;
}

bool CXXMacroFunctionDefinition::hasVarargs() const {
  if (parameters.empty()) {
    return false;
  }
  return parameters[parameters.size() - 1] == "...";
}

CXXMacroFunctionDefinition::CXXMacroFunctionDefinition(
    const std::string &name,
    std::vector<std::string> parameters
) : CXXMacroDefinition(name), parameters(std::move(parameters)){}

std::string CXXMacroFunctionDefinition::toString() const {
  std::string str = "CXXMacroFunctionDefinition(";
  str += "\"";
  str += name;
  str += "\"";
  if (!parameters.empty()) {
    str += ", ";
    str += jen::strings::join(parameters);
  }
  str += ")";
  return str;
}

CXXMacroDefinition::CXXMacroDefinition(const std::string &name) : CXXNamed(name) {}

CXXMacroConstantDefinition::CXXMacroConstantDefinition(const std::string &name, std::string value)
    : CXXMacroDefinition(name), value(std::move(value)) {}

std::string CXXMacroConstantDefinition::toString() const {
  std::string str = "CXXMacroConstantDefinition(\"";
  str += name;
  str += "\", \"";
  str += value;
  str += "\")";
  return str;
}
}
