#include <Lucid.hpp>

int main() {
    int a = 10;
    Lucid_Script script("../example/Script.lc");
    script.AddVariable(&a, "a");

    script.Tokenize();

    std::cout << "Tokens: " << std::endl;
    script._TestTokens();

    std::cout << std::endl << "Output: " << std::endl;
    script.Execute("main");

    std::cout << std::endl << "Lucid Variables: " << std::endl;
    script._TestVariables();
    std::cout << std::endl << "C++ Variables: " << std::endl;
    script._TestCppVariables();

    return 0;
}