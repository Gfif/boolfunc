#include "bf.h"

int main() {
    std::string s;
    std::cin >> s;
    bf a(s);
    std::cout << a.u() << std::endl;
    a.anf();
    std::cout << std::endl;
    std::cout << "deg " << (int)a.deg() << std::endl;
    LONG *b;
    UCHAR n = a.getN();
    b = new LONG[(1 << n)];
    a.walsh(b);
    std::cout << "u " << a.u() << std::endl;
    for (BASE i = 0; i < (1 << n); i++) {
        std::cout << b[i] << " ";
    }
    std::cout << std::endl;
    delete [] b;
    std::cout << "cor " << (int)a.cor() << std::endl;
    std::cout << "Nf " << (int)a.Nf() << std::endl;
    std::cout << "NAP " << a.NAP() << std::endl;
    std::cout << "CNf " << (int)a.CNf() << std::endl;
    std::cout << "PC " << (int)a.PC() << std::endl;
    b = new LONG[(1 << n)];
    a.autocor(b);
    for (BASE i = 0; i < (1 << n); i++) {
        std::cout << b[i] << " ";
    }
    std::cout << std::endl;
    delete [] b;
    return 0;
}
