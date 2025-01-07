#pragma once
#include <LucidData.hpp>

class Lucid_Script {
    public:
        Lucid_Script(const char *file);
        void Tokenize();
        void Execute(const std::string &funcName);
        void _TestTokens();

    private:
        std::vector<Lucid_Token> m_tokens;
        std::vector<Lucid_Variable> m_variables;
        std::string m_contents;
        bool m_stringQuotation;

        void NewToken(const std::string &name);
        void NewCharToken(const char &key);
        bool CharScan(const char &key);
        void LucidPrint(const std::string &input);
        void LucidError(const uint32_t &id, const std::string &arg);
};