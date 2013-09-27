#include "bf.h"

int main() {
    UCHAR n;
    std::string s;
    std::cin >> s;
    std::cout << s << std::endl;
    bf a(s);
    std::cout << a << std::endl;
    return 0;
}
