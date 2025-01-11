#pragma once
#include <LucidData.hpp>

class Lucid_Script {
    public:
        Lucid_Script(const char *file);
        void Tokenize();
        void Execute(const std::string &funcName);
        void _TestTokens();
        void _TestVariables();

    private:
        std::vector<Lucid_Token> m_tokens;
        std::unordered_map<std::string, Lucid_DataType*> m_variables;
        std::string m_contents;
        bool m_stringQuotation;

        bool CharScan(const char &key);
        Lucid_DataType GetTypeFromString(const std::string &name);
        void NewToken(const std::string &name);
        void NewCharToken(const char &key);
        void LucidPrint(const std::string &input);
        void LucidError(const uint32_t &id, const std::string &arg);
        void LucidLog(const std::string &log);
};

struct Lucid_VariableFunctors {
    void operator()(const int &value) {
        std::cout << value << " (int)";
    }

    void operator()(const float &value) {
        std::cout << value << " (float)";
    }

    void operator()(const double &value) {
        std::cout << value << " (double)";
    }

    void operator()(const std::string &value) {
        std::cout << value << " (string)";
    }
};