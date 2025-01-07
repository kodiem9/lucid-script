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

struct Lucid_Token {
    Lucid_TokenType type;
    std::string value;
};