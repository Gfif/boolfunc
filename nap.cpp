#include "bf.h"

int main() {
    std::string s;
    std::cin >> s;
    bf a(s);
    std::cout << a.NAP() << std::endl;
    return 0;
}
