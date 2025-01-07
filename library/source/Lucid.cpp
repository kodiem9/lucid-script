#include <Lucid.hpp>

Lucid_Script::Lucid_Script(const char *file) {
    std::ifstream script(file);
    std::stringstream strStream;
    strStream << script.rdbuf();
    contents = strStream.str();
}

void Lucid_Script::Tokenize() {
    std::string buffer;
    char key;

    for (size_t i = 0; i < contents.length()-1; i++) {
        key = contents[i];

        if (isspace(key)) {
            if (buffer.length() > 0) {
                std::cout << buffer << std::endl;
                buffer.clear();
            }
            continue;
        }

        if (ispunct(key)) {
            if (buffer.length() > 0) {
                std::cout << buffer << std::endl;
                buffer.clear();
            }
            std::cout << key << std::endl;
            continue;
        }

        buffer += key;
    }

    std::cout << buffer << std::endl;
    buffer.clear();
}