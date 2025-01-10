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

    ERROR
};

using Lucid_DataType = std::variant<int, float, double, std::string>;

struct Lucid_Token {
    Lucid_TokenType type;
    std::string value;
};