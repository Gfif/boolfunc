#include "bf.h"

int main(int argc, char* argv[]) {
    UCHAR n;
    std::string s;
    std::cin >> s;
    bf a(s);
    LONG *b;
    n = a.getN();
    b = new LONG[(1 << n)];
    a.autocor(b);
    for (BASE i = 0; i < (1 << n); i++) {
        std::cout << b[i] << " ";
    }
    std::cout << std::endl;
    delete [] b;
    return 0;
}
