#include <Lucid.hpp>

int main() {
    Lucid_Script script("../example/Script.lc");

    script.Tokenize();
    script._TestTokens();

    return 0;
}