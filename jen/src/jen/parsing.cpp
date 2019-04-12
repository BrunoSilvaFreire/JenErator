#include <utility>

#include <cassert>
#include "tokenization.cpp"

namespace jen {
#define PARSING_STATE_PARAMS size_t &i,  std::vector<CXXToken> &tokens, CXXTranslationUnit &unit, const ParseOptions &options

void consume_whitespace(size_t &i, std::vector<CXXToken> &tokens) {
  for (; i < tokens.size(); ++i) {
    if (tokens[i].getCharacterType() != CXXCharacterType::eWhiteSpace) {
      break;
    }
  }
}

std::string join_until_encounter(size_t &i, const std::vector<CXXToken> &tokens, const std::string &content) {
  auto str = std::string();
  for (; i < tokens.size(); i++) {
    auto c = tokens[i].getContent();
    if (c == content) {
      break;
    }
    str += c;
  }
  return str;
}

void try_include_file(PARSING_STATE_PARAMS) {
  consume_whitespace(i, tokens);
  const auto &token = tokens[i++];
  //assert(token.getCharacterType() == CXXCharacterType::eSymbol);

  std::cout << "Token: " << token << std::endl;
  assert(token.getContent() == "<" || token.getContent() == "\"");
  const auto &file = join_until_encounter(i, tokens, ">");
  std::cout << "File: " << file << std::endl;
  std::filesystem::path found;
  if (!options.tryFindFile(file, found)) {
    return;
  }
  std::cout << "Found @ " << found << std::endl;
}

void parse_preprocessor(PARSING_STATE_PARAMS) {
  const CXXToken &initial = tokens[i++];
  if (initial.getContent() == "include") {
    try_include_file(i, tokens, unit, options);
    return;
  }
  std::cout << initial.getContent() << std::endl;
  /*

  for (; i < tokens.size(); ++i) {

  }

  */
}

CXXTranslationUnit parse(std::istream &stream, const ParseOptions &parseOptions) {
  auto tokens = tokenize(stream);
  CXXTranslationUnit translationUnit;
  for (size_t i = 0; i < tokens.size(); ++i) {
    const CXXToken &token = tokens[i];
    const std::string &content = token.getContent();
    switch (token.getCharacterType()) {
      case eNone:break;
      case eWhiteSpace:break;
      case eSymbol:
        if (content == "#") {
          parse_preprocessor(++i, tokens, translationUnit, parseOptions);
        }
        break;
      case eNumber:break;
      case eWord:break;
    }
    std::cout << "(" << jen::toString(token.getCharacterType()) << ") '" << token.getContent() << "'"
              << std::endl;
  }
  return translationUnit;
}

ParseOptions::ParseOptions(
    std::vector<std::filesystem::path> headersSearchPaths
) : headersSearchPaths(std::move(headersSearchPaths)) {

}

const ParseOptions::HeaderPaths &ParseOptions::getHeadersSearchPaths() const {
  return headersSearchPaths;
}

bool ParseOptions::tryFindFile(const std::string &file, std::filesystem::path &result) const {
  for (const std::filesystem::path &path : headersSearchPaths) {
    std::filesystem::path potential = path / file;
    if (std::filesystem::exists(potential)) {
      result = potential;
      return true;
    }
  }
  return false;
}
}