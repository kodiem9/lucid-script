#include <Lucid.hpp>

int main() {
    Lucid_Script script("../example/Script.lc");

    script.Tokenize();

    std::cout << "Tokens: " << std::endl;
    script._TestTokens();

    std::cout << std::endl << "Output: " << std::endl;
    script.Execute("main");

    std::cout << std::endl << "Variables: " << std::endl;
    script._TestVariables();

    return 0;
}