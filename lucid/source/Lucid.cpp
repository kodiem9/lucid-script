#include <Lucid.hpp>

#define SET_TO_OPPOSITE_BOOL(var) (var) ? false : true

Lucid_Script::Lucid_Script(const char *file)
    : m_stringQuotation(false) {
    std::ifstream script(file);
    std::stringstream strStream;
    strStream << script.rdbuf();
    m_contents = strStream.str();
}

void Lucid_Script::Tokenize() {
    std::string buffer;
    char key;

    for (size_t i = 0; i < m_contents.length()-1; i++) {
        key = m_contents[i];

        if (CharScan(key)) {
            if (isspace(key)) {
                if (buffer.length() > 0) {
                    NewToken(buffer);
                    buffer.clear();
                }
                continue;
            }

            if (ispunct(key)) {
                if (key == '.' && buffer.size() > 0 && isdigit(buffer[0])) {
                    // Do nothing...
                }
                else {
                    if (buffer.length() > 0) {
                        NewToken(buffer);
                        buffer.clear();
                    }
                    NewCharToken(key);
                    continue;
                }
            }
        }

        buffer += key;
    }

    if (buffer.length() > 0)
        NewToken(buffer);
    else
        NewCharToken(key);
}

void Lucid_Script::Execute(const std::string &funcName) {
    for (size_t i = 0; i < m_tokens.size(); i++) {
        switch (m_tokens[i].type) {
            // Callign Lucid variable
            case Lucid_TokenType::VARIABLE: {

            }

            // Calling C++ variable
            case Lucid_TokenType::DOLLAR_SIGN: {
                
            }

            // Macro related things (functions, keywords etc.)
            case Lucid_TokenType::MACRO: {
            
            }

            default: break;
        }
    }
}


/*     PRIVATE     */
bool Lucid_Script::CharScan(const char &key) {
    // If quotation is true, ignore all keys, but if it's a quotation again (when true), turn it to false
    return (!m_stringQuotation || (m_stringQuotation && key == '"'));
}

void Lucid_Script::NewToken(const std::string &name) {
    Lucid_Token temp;

    if (name == "func") {
        temp.type = Lucid_TokenType::FUNCTION_KEYWORD;
    }
    else if (m_stringQuotation) {
        temp.type = Lucid_TokenType::DATA_TYPE;
        temp.value = name;
    }
    else {
        // Check the prevous token. If no tokens were made the program will break!
        const Lucid_Token &prevToken = m_tokens[m_tokens.size()-1];

        switch (prevToken.type) {
            case Lucid_TokenType::FUNCTION_KEYWORD:
                temp.type = Lucid_TokenType::FUNCTION_NAME; break;
            case Lucid_TokenType::MACRO:
                temp.type = Lucid_TokenType::FUNCTION_NAME; break;
            case Lucid_TokenType::EQUAL: {
                if (isalpha(name[0]))
                    temp.type = Lucid_TokenType::VARIABLE;
                else
                    temp.type = Lucid_TokenType::DATA_TYPE;
                break;
            }
            default:
                temp.type = Lucid_TokenType::VARIABLE;
        }
        temp.value = name;
    }

    m_tokens.emplace_back(temp);
}

void Lucid_Script::NewCharToken(const char &key) {
    Lucid_Token temp;

    switch (key) {
        case '(':
            temp.type = Lucid_TokenType::PARENTHESES_OPEN; break;
        case ')':
            temp.type = Lucid_TokenType::PARENTHESES_CLOSE; break;
        case '{':
            temp.type = Lucid_TokenType::BRACKETS_OPEN; break;
        case '}':
            temp.type = Lucid_TokenType::BRACKETS_CLOSE; break;
        case '=':
            temp.type = Lucid_TokenType::EQUAL; break;
        case '@':
            temp.type = Lucid_TokenType::MACRO; break;
        case '!':
            temp.type = Lucid_TokenType::EXCLAMATION; break;
        case ',':
            temp.type = Lucid_TokenType::COMMA; break;
        case ';':
            temp.type = Lucid_TokenType::SEMICOLON; break;
        case '$':
            temp.type = Lucid_TokenType::DOLLAR_SIGN; break;
        case '"':
            m_stringQuotation = SET_TO_OPPOSITE_BOOL(m_stringQuotation); break;
        default:
            temp.type = Lucid_TokenType::ERROR;
    }

    if (key != '"')
        m_tokens.emplace_back(temp);
}

void Lucid_Script::LucidError(const uint32_t &id, const std::string &arg) {
    std::cout << "[ERROR #" << id << "]\t";
    switch (id) {
        case 0: {
            std::cout << "Expected an equal sign after initializing/calling a variable!" << std::endl;
            std::cout << arg << " = ..." << std::endl;
            break;
        }
        default: std::cout << "Unrecognizable error occured!" << std::endl;
    }
}

void Lucid_Script::LucidLog(const std::string &log) {
    std::cout << "[LUCID] " << log << std::endl;
}

// Remove later!!!
void Lucid_Script::_TestTokens() {
    size_t index = 0;

    for (const Lucid_Token &token: m_tokens) {
        std::cout << index << "\t";
        switch (token.type) {
            case Lucid_TokenType::FUNCTION_KEYWORD:
                std::cout << "FUNCTION_KEYWORD" << std::endl; break;
            case Lucid_TokenType::FUNCTION_NAME:
                std::cout << "FUNCTION_NAME: \"" << token.value << "\"" << std::endl; break;
            case Lucid_TokenType::VARIABLE:
                std::cout << "VARIABLE: \"" << token.value << "\"" << std::endl; break;
            case Lucid_TokenType::DATA_TYPE:
                std::cout << "DATA_TYPE: \"" << token.value << "\"" << std::endl; break;
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
            case Lucid_TokenType::SEMICOLON:
                std::cout << "SEMICOLON" << std::endl; break;
            case Lucid_TokenType::EQUAL:
                std::cout << "EQUAL" << std::endl; break;
            case Lucid_TokenType::COMMA:
                std::cout << "COMMA" << std::endl; break;
            case Lucid_TokenType::EXCLAMATION:
                std::cout << "EXCLAMATION" << std::endl; break;
            case Lucid_TokenType::ERROR:
                std::cout << "ERROR" << std::endl; break;
            default:
                std::cout << "UNKNOWN TOKEN" << std::endl;
        }
        index++;
    }
}