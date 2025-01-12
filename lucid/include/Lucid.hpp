#pragma once
#include <LucidData.hpp>

class Lucid_Script {
    public:
        Lucid_Script(const char *file);
        void Tokenize();
        void Execute(const std::string &funcName);
        template<typename T> void AddVariable(T *variable, const std::string &name);
        void _TestTokens();
        void _TestVariables();
        void _TestCppVariables();

    private:
        std::vector<Lucid_Token> m_tokens;
        Lucid_VariablesMap m_variables;
        Lucid_CppVariablesMap m_cppVariables;
        std::string m_contents;
        bool m_stringQuotation;

        bool CharScan(const char &key);
        Lucid_DataType GetTypeFromString(const std::string &name);
        void NewToken(const std::string &name);
        void NewCharToken(const char &key);
        void LucidPrint(const Lucid_DataType &input);
        void LucidError(const uint32_t &id, const std::string &arg);
        void LucidLog(const std::string &log);
};

template<typename T>
void Lucid_Script::AddVariable(T *variable, const std::string &name) {
    m_cppVariables[name] = variable;
}