#include "bf.h"

int main() {
    std::string s;
    std::cin >> s;
    bf a(s);
    std::cout << (int)a.Nf() << std::endl;
    return 0;
}
