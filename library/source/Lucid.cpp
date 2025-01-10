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

    buffer.clear();
}

void Lucid_Script::Execute(const std::string &funcName) {
    for(size_t i = 0; i < m_tokens.size(); i++) {
        switch (m_tokens[i].type) {
            case Lucid_TokenType::VARIABLE: {
                bool variableFound = false;
                size_t variableIndex;

                for (variableIndex = 0; variableIndex < m_variables.size(); variableIndex++) {
                    if (m_variables[variableIndex].name == m_tokens[i].value) {
                        variableFound = true;
                        break;
                    }
                }

                Lucid_Variable temp;
                temp.name = m_tokens[i].value;

                // Go to equal and check if correct
                if (m_tokens[++i].type != Lucid_TokenType::EQUAL) {
                    LucidError(0, m_tokens[i-1].value);
                    return;
                }

                // Go to the data given to the variable
                temp.value = m_tokens[++i].value;

                if (variableFound)
                    m_variables[variableIndex] = temp;
                else
                    m_variables.push_back(temp);
                
                break;
            }
            case Lucid_TokenType::MACRO: {
                if (m_tokens[++i].value == "log") {
                    std::string input;
                    
                    if (m_tokens[++i].type == Lucid_TokenType::QUOTATION_OPEN) {
                        input = m_tokens[++i].value;
                        i++; // Exit quotation
                        LucidPrint(input);
                    }
                }

                break;
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
        temp.type = Lucid_TokenType::STRING;
        temp.value = name;
    }
    else {
        // Check the prevous token. If no tokens were made the program will break!
        switch (m_tokens[m_tokens.size()-1].type) {
            case Lucid_TokenType::FUNCTION_KEYWORD:
                temp.type = Lucid_TokenType::FUNCTION_NAME; break;
            case Lucid_TokenType::MACRO:
                temp.type = Lucid_TokenType::FUNCTION_NAME; break;
            case Lucid_TokenType::EQUAL:
                temp.type = Lucid_TokenType::NUMBER; break;
            default:
                temp.type = Lucid_TokenType::VARIABLE;
        }
        temp.value = name;
    }

    m_tokens.push_back(temp);
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
        case '"': {
            if (m_stringQuotation)
                temp.type = Lucid_TokenType::QUOTATION_CLOSE;
            else
                temp.type = Lucid_TokenType::QUOTATION_OPEN;
            
            m_stringQuotation = SET_TO_OPPOSITE_BOOL(m_stringQuotation);
            break;
        }
        default:
            temp.type = Lucid_TokenType::ERROR;
    }

    m_tokens.push_back(temp);
}

void Lucid_Script::LucidPrint(const std::string &input) {
    std::cout << input << std::endl;
}

void Lucid_Script::LucidError(const uint32_t &id, const std::string &arg) {
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
    for (const Lucid_Token &token: m_tokens) {
        switch (token.type) {
            case Lucid_TokenType::FUNCTION_KEYWORD:
                std::cout << "FUNCTION_KEYWORD" << std::endl; break;
            case Lucid_TokenType::FUNCTION_NAME:
                std::cout << "FUNCTION_NAME: \"" << token.value << "\"" << std::endl; break;
            case Lucid_TokenType::VARIABLE:
                std::cout << "VARIABLE: \"" << token.value << "\"" << std::endl; break;
            case Lucid_TokenType::NUMBER:
                std::cout << "NUMBER: \"" << token.value << "\"" << std::endl; break;
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
    }
}