#include <utility>

#include <jen/parsing.h>
#include <iostream>

namespace jen {
enum CXXCharacterType {
  eNone,
  eWhiteSpace,
  eSymbol,
  eNumber,
  eWord,
};

template<typename CXXCharacterType>
std::string toString(CXXCharacterType characterType) {
  switch (characterType) {
    case eNone:return "None";
    case eWhiteSpace:return "WhiteSpace";
    case eSymbol:return "Symbol";
    case eNumber:return "Number";
    case eWord:return "Word";
  }
  return "Unknown";
}

CXXCharacterType getCharacterTypeFor(char c) {
  if (isdigit(c)) {
    return CXXCharacterType::eNumber;
  }
  if (isalpha(c)) {
    return CXXCharacterType::eWord;
  }
  if (isspace(c)) {
    return CXXCharacterType::eWhiteSpace;
  }
  if (ispunct(c)) {
    return CXXCharacterType::eSymbol;
  }
  return CXXCharacterType::eNone;
}

class CXXToken {
 private:
  std::string content;
  CXXCharacterType characterType;
 public:
  CXXToken(
      std::string content,
      CXXCharacterType characterType
  ) : content(std::move(content)), characterType(characterType) {}

  const std::string &getContent() const {
    return content;
  }

  bool isWhiteSpace() {

    for (const char &c : content) {
      if (!isspace(c)) {
        return c;
      }
    }
    return true;
  }

  CXXCharacterType getCharacterType() const {
    return characterType;
  }

  bool operator==(const std::string &other) {
    return content == other;
  }

  bool operator==(const char *other) {
    return content == other;
  }

  friend std::ostream &operator<<(std::ostream &os, const CXXToken &token) {
    return os << "CXXToken(\"" << token.content << "\", " << jen::toString(token.characterType) << ")";
  }
};

std::vector<CXXToken> tokenize(std::istream &stream) {

  std::string currentToken = std::string();
  std::vector<CXXToken> tokens = std::vector<CXXToken>();
  char currentChar = 0;
  CXXCharacterType tokenType;
  CXXCharacterType lastType = CXXCharacterType::eNone;
  while (stream.get(currentChar)) {
    tokenType = getCharacterTypeFor(currentChar);
    if (lastType != CXXCharacterType::eNone && tokenType != lastType) {
      tokens.emplace_back(currentToken, lastType);
      currentToken = std::string();

    }
    currentToken += currentChar;
    lastType = tokenType;
  }
  return tokens;
}

}