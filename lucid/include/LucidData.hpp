#pragma once
#include <LIB_PCH.hpp>

enum class Lucid_TokenType {
    FUNCTION_KEYWORD,
    FUNCTION_NAME,
    VARIABLE,
    DATA_TYPE,

    PARENTHESES_OPEN,
    PARENTHESES_CLOSE,
    BRACKETS_OPEN,
    BRACKETS_CLOSE,

    MACRO,
    EXCLAMATION,
    COMMA,
    EQUAL,
    SEMICOLON,
    DOLLAR_SIGN,

    ERROR
};

using Lucid_DataType = std::variant
    <
        int,
        float,
        double,
        std::string
    >;

using Lucid_CppDataType = std::variant
    <
        int*,
        float*,
        double*,
        std::string*
    >;

using Lucid_VariablesMap = std::unordered_map<std::string, Lucid_DataType>;
using Lucid_CppVariablesMap = std::unordered_map<std::string, Lucid_CppDataType>;

struct Lucid_Token {
    Lucid_TokenType type;
    std::string value;
};

struct Lucid_VariableFunctors {
    void operator()(const int &value);
    void operator()(const float &value);
    void operator()(const double &value);
    void operator()(const std::string &value);
    void operator()(const int *value);
    void operator()(const float *value);
    void operator()(const double *value);
    void operator()(const std::string *value);
};