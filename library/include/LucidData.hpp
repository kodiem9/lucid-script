#pragma once
#include <LIB_PCH.hpp>

enum class Lucid_TokenType {
    FUNCTION_KEYWORD,
    FUNCTION_NAME,
    VARIABLE,

    PARENTHESES_OPEN,
    PARENTHESES_CLOSE,
    BRACKETS_OPEN,
    BRACKETS_CLOSE,
    QUOTATION_OPEN,
    QUOTATION_CLOSE,

    MACRO,
    EXCLAMATION,
    COMMA,
    EQUAL,
    SEMICOLON,

    STRING,
    NUMBER,

    ERROR
};

// Maybe Lucid_Int, Lucid_Bool, Lucid_Float, Lucid_Double, Lucid_String in the future...?
struct Lucid_Variable {
    std::string name;
    std::string value;
};

using Lucid_DataType = std::variant<int, float, double, std::string>;

struct Lucid_Token {
    Lucid_TokenType type;
    std::string value;
};