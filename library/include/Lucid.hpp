#pragma once
#include <LIB_PCH.hpp>

class Lucid_Script {
    public:
        Lucid_Script(const char *file);
        void Tokenize();

    private:
        std::string contents;
};