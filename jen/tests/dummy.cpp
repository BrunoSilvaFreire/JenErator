#include <jen/jen.h>
#include <jen/parsing.h>
#include <jen/cpp/preprocessors.h>
#include <fstream>
#include <iostream>
#include <filesystem>

#define SERIALIZE(...)
#define HELLO auto stuff = "smt"

class DummyApp {

    SERIALIZE(Dummy, Value, HideInInspector, Cachaça, ひらがな)
    bool boolean;
private:
    int a;
};

void print(jen::CXXTranslationUnit &unit, size_t &indent) {
    HELLO;
    const auto &elements = unit.getElements();
    for (const auto &e:unit.getElements()) {
        jen::CXXInclude *candidate;
        std::cout << std::string(indent * 2, ' ') << e->toString() << std::endl;
        if ((candidate = dynamic_cast<jen::CXXInclude *>(e)) != nullptr) {
            print(candidate->getTranslationUnit(), ++indent);
            indent--;
        } else {
        }
    }
}

int main(int argc, char **argv) {
    std::string str;
    for (int i = 1; i < argc; ++i) {
        str += argv[i];
    }
    //auto path = std::filesystem::absolute(str);
    auto hdr = std::filesystem::absolute(std::filesystem::current_path() / "../../../jen/include");
    std::cout << "Using file " << hdr << std::endl;
    jen::ParseOptions opt(jen::ParseOptions::HeaderPaths({hdr}));
    std::ifstream file(str);
    if (!file.good()) {
        std::cout << "Path " << hdr << " doesn't exist" << std::endl;
        return 1;
    }
    jen::CXXTranslationUnit unit = jen::parse(file, opt);
    size_t indent = 0;
    std::cout << "Printing" << std::endl;
    print(unit, indent);
    file.close();
}