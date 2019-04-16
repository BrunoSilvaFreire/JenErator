#include <utility>

#include <cassert>
#include <fstream>
#include "tokenization.cpp"
#include <jen/cpp/preprocessors.h>
#include <vector>
#include <functional>
#include <jen/utilities/strings.h>

namespace jen {
#define PARSING_STATE_PARAMS size_t &i,  std::vector<CXXToken> &tokens, CXXTranslationUnit &unit, const ParseOptions &options
#define CREATE_DELIMITERS(...) std::vector<const char *>({ __VA_ARGS__ })

    void consume_whitespace(size_t &i, std::vector<CXXToken> &tokens) {
        for (; i < tokens.size(); ++i) {
            if (tokens[i].getCharacterType() != CXXCharacterType::eWhiteSpace) {
                break;
            }
        }
    }

    void consume_whitespace_nonewline(size_t &i, std::vector<CXXToken> &tokens) {
        for (; i < tokens.size(); ++i) {
            const auto &t = tokens[i];
            if (t.getCharacterType() != CXXCharacterType::eWhiteSpace || t.hasNewLine()) {
                break;
            }
        }
    }

    std::string join_until_encounter(size_t &i, const std::vector<CXXToken> &tokens,
                                     const std::vector<const char *> &delimiters) {
        auto str = std::string();
        for (; i < tokens.size(); i++) {
            auto c = tokens[i].getContent();
            if (std::any_of(delimiters.begin(), delimiters.end(), [&](const char *d) {
                return jen::strings::starts_with(c, d);
            })) {
                break;
            }

            str += c;
        }
        return str;
    }

    std::string readMacroValue(size_t &i, std::vector<CXXToken> &tokens) {
        auto str = std::string();
        consume_whitespace_nonewline(i, tokens);
        for (; i < tokens.size(); i++) {
            auto &t = tokens[i];
            auto &c = t.getContent();
            if (t.hasNewLine()) {
                break;
            }
            str += c;
        }
        return str;
    }

    std::vector<std::string> readMacroParameters(size_t &i, std::vector<CXXToken> &tokens) {
        auto params = std::vector<std::string>();
        std::string str;
        for (; i < tokens.size(); i++) {
            auto &t = tokens[i];
            auto &c = t.getContent();
            if (c == ")") {
                params.emplace_back(str);
                break;
            }
            if (c == ",") {
                params.emplace_back(str);
                str = "";
            } else {
                str += c;
            }
        }
        return params;
    }

    void try_parse_define(PARSING_STATE_PARAMS) {
        consume_whitespace(i, tokens);
        const auto &macroName = join_until_encounter(i, tokens, CREATE_DELIMITERS(" ", "(", "\n"));
        auto &post = tokens[i];
        const auto &postCt = post.getContent();
        if (jen::strings::starts_with(postCt, "(")) {
            // is macro function
            std::vector<std::string> parameters;
            if (!jen::strings::contains(postCt, ")")) {
                parameters = readMacroParameters(++i, tokens);
            }
            unit.getElements().emplace_back(
                    new jen::CXXMacroFunctionDefinition(macroName, parameters)
            );
        } else {
            std::string value = readMacroValue(i, tokens);
            unit.getElements().emplace_back(
                    new jen::CXXMacroConstantDefinition(macroName, value)
            );
        }
    }

    bool try_include_file(PARSING_STATE_PARAMS) {
        consume_whitespace(i, tokens);
        const auto &token = tokens[i++];
        const auto &file = join_until_encounter(i, tokens, CREATE_DELIMITERS(">"));
        std::filesystem::path found;
        jen::CXXInclude::Type type;
        switch (token.getContent()[0]) {
            case '<':
                type = CXXInclude::Type::eBrackets;
                break;
            case '"':
                type = CXXInclude::Type::eQuotes;
                break;
            default:
                throw std::runtime_error("Unknown include character");
        }
        if (!options.tryFindFile(file, found)) {
            std::cout << "Unable to find file '" << file << "'" << std::endl;
            return false;
        }

        auto stream = std::ifstream(found);
        auto newTokens = jen::parse(stream, options);
        unit.getElements().emplace_back(new jen::CXXInclude(file, type, newTokens));
        stream.close();
        return true;
    }

    void parse_preprocessor(PARSING_STATE_PARAMS) {
        const CXXToken &initial = tokens[i++];
        const auto &ct = initial.getContent();
        if (ct == "include") {
            try_include_file(i, tokens, unit, options);
            return;
        }
        if (ct == "define") {
            try_parse_define(i, tokens, unit, options);
            return;
        }
    }

    CXXTranslationUnit parse(std::istream &stream, const ParseOptions &parseOptions) {
        auto tokens = tokenize(stream);
        CXXTranslationUnit translationUnit;
        for (size_t i = 0; i < tokens.size(); i++) {
            const CXXToken &token = tokens[i];
            const std::string &content = token.getContent();
            switch (token.getCharacterType()) {
                case eNone:
                    break;
                case eWhiteSpace:
                    break;
                case eSymbol:
                    if (content == "#") {
                        parse_preprocessor(++i, tokens, translationUnit, parseOptions);
                    }
                    break;
                case eNumber:
                    break;
                case eWord:
                    break;
            }

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
            std::filesystem::path potential = std::filesystem::absolute(path / file);
            if (std::filesystem::exists(potential)) {
                result = potential;
                return true;
            }
        }
        return false;
    }
}