#include "bf.h"

int main(int argc, char* argv[]) {
    UCHAR n;
    std::string s;
    std::cin >> s;
    bf a(s);
    std::cout << a << std::endl << a.u() << std::endl << a.u().u() << std::endl;
    return 0;
}
