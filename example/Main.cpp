#include <Lucid.hpp>

int main() {
    Lucid_Script script("../example/Script.lc");
    
    script.Tokenize();
    script._TestTokens();
    script.Execute("main");

    return 0;
}