#include <Lucid.hpp>

#define SET_TO_OPPOSITE_BOOL(var) (var) ? false : true

Lucid_Script::Lucid_Script(const char *file)
    : stringQuotation(false) {
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

        if (CharScan(key)) {
            if (isspace(key)) {
                if (buffer.length() > 0) {
                    NewToken(buffer);
                    buffer.clear();
                }
                continue;
            }

            if (ispunct(key)) {
                if (buffer.length() > 0) {
                    NewToken(buffer);
                    buffer.clear();
                }
                NewCharToken(key);
                continue;
            }
        }

        buffer += key;
    }

    std::cout << buffer << std::endl;
    buffer.clear();
}

bool Lucid_Script::CharScan(const char &key) {
    // If quotation is true, ignore all keys, but if it's a quotation again (when true), turn it to false
    return (!stringQuotation || (stringQuotation && key == '"'));
}

void Lucid_Script::NewToken(const std::string &name) {
    Lucid_Token temp;

    if (name == "func") {
        temp.type = Lucid_TokenType::FUNCTION_KEYWORD;
    }
    else if (stringQuotation) {
        temp.type = Lucid_TokenType::STRING;
        temp.value = name;
    }
    else {
        temp.type = Lucid_TokenType::FUNCTION_NAME;
        temp.value = name;
    }

    tokens.push_back(temp);
}

void Lucid_Script::NewCharToken(const char &key) {
    Lucid_Token temp;

    switch(key) {
        case '(':
            temp.type = Lucid_TokenType::PARENTHESES_OPEN; break;
        case ')':
            temp.type = Lucid_TokenType::PARENTHESES_CLOSE; break;
        case '{':
            temp.type = Lucid_TokenType::BRACKETS_OPEN; break;
        case '}':
            temp.type = Lucid_TokenType::BRACKETS_CLOSE; break;
        case '@':
            temp.type = Lucid_TokenType::MACRO; break;
        case '!':
            temp.type = Lucid_TokenType::EXCLAMATION; break;
        case ',':
            temp.type = Lucid_TokenType::COMMA; break;
        case ';':
            temp.type = Lucid_TokenType::SEMICOLON; break;
        case '"': {
            if (stringQuotation)
                temp.type = Lucid_TokenType::QUOTATION_CLOSE;
            else
                temp.type = Lucid_TokenType::QUOTATION_OPEN;
            
            stringQuotation = SET_TO_OPPOSITE_BOOL(stringQuotation);
            break;
        }
        default:
            temp.type = Lucid_TokenType::ERROR;
    }

    tokens.push_back(temp);
}

// Remove later!!!
void Lucid_Script::_TestTokens() {
    for(const Lucid_Token &token: tokens) {
        switch(token.type) {
            case Lucid_TokenType::FUNCTION_KEYWORD:
                std::cout << "FUNCTION_KEYWORD" << std::endl; break;
            case Lucid_TokenType::FUNCTION_NAME:
                std::cout << "FUNCTION_NAME: \"" << token.value << "\"" << std::endl; break;
            case Lucid_TokenType::PARENTHESES_OPEN:
                std::cout << "PARENTHESES_OPEN" << std::endl; break;
            case Lucid_TokenType::PARENTHESES_CLOSE:
                std::cout << "PARENTHESES_CLOSE" << std::endl; break;
            case Lucid_TokenType::BRACKETS_OPEN:
                std::cout << "BRACKETS_OPEN" << std::endl; break;
            case Lucid_TokenType::BRACKETS_CLOSE:
                std::cout << "BRACKETS_CLOSE" << std::endl; break;
            case Lucid_TokenType::MACRO:
                std::cout << "MACRO" << std::endl; break;
            case Lucid_TokenType::QUOTATION_OPEN:
                std::cout << "QUOTATION_OPEN" << std::endl; break;
            case Lucid_TokenType::QUOTATION_CLOSE:
                std::cout << "QUOTATION_CLOSE" << std::endl; break;
            case Lucid_TokenType::STRING:
                std::cout << "STRING: \"" << token.value << "\"" << std::endl; break;
            case Lucid_TokenType::SEMICOLON:
                std::cout << "SEMICOLON" << std::endl; break;
            case Lucid_TokenType::COMMA:
                std::cout << "COMMA" << std::endl; break;
            case Lucid_TokenType::EXCLAMATION:
                std::cout << "EXCLAMATION" << std::endl; break;
            case Lucid_TokenType::ERROR:
                std::cout << "ERROR" << std::endl; break;
            default:
                std::cout << "UNKNOWN TOKEN" << std::endl;
        }
    }
}