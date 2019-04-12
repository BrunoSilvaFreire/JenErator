#include <jen/jen.h>
#include <jen/parsing.h>
#include <fstream>
#include <iostream>
#include <filesystem>

#define SERIALIZE(...)

class DummyApp {

    SERIALIZE(Dummy, Value, HideInInspector, Cachaça, ひらがな)
    bool boolean;
private:
    int a;
};

int main(int argc, char **argv) {
    std::string str;
    for (int i = 1; i < argc; ++i) {
        str += argv[i];
    }
    //auto path = std::filesystem::absolute(str);
    std::ifstream file(str);
    if (!file.good()) {
        std::cout << "Path " << str << " doesn't exist" << std::endl;
        return 1;
    }
    jen::CXXTranslationUnit unit = jen::parse(file);
    file.close();
}