#include <Lucid.hpp>

int main() {
    int a = 10;
    Lucid_Script script("../example/Script.lc");

    script.Tokenize();

    std::cout << "Tokens: " << std::endl;
    script._TestTokens();

    std::cout << std::endl << "Output: " << std::endl;
    script.Execute("main");

    return 0;
}