#include "bf.h"

int main(int argc, char* argv[]) {
    UCHAR n;
    switch(argc) {
        case 2:
            n = atoi(argv[1]);
            break;
        default:
            std::cout << "Usage: " << argv[0] << " n" << std::endl;
            return 1;
    }
    srand(time(NULL));
    bf a(n, 1);
    std::cout << a << std::endl << a.u() << std::endl;
    a.anf();
    std::cout << (int)a.deg() << std::endl;
    return 0;
}
