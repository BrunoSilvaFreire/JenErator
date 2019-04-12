#include <utility>

#ifndef JENERATOR_PARSING_H
#define JENERATOR_PARSING_H

#include <istream>
#include <filesystem>
#include <jen/cpp/cpp.h>

namespace jen {

    class ParseOptions {
    public:
        typedef std::vector<std::filesystem::path> HeaderPaths;
    private:
        HeaderPaths headersSearchPaths;
    public:

        explicit ParseOptions(
                HeaderPaths headersSearchPaths = HeaderPaths()
        );

        const HeaderPaths &getHeadersSearchPaths() const;

        bool tryFindFile(const std::string &file, std::filesystem::path &result) const;
    };

    CXXTranslationUnit parse(std::istream &stream, const ParseOptions &options = ParseOptions());

}
#endif
