#include "bf.h"

bf:: bf(LONG size) {
    n = size;
    LONG bitsize = getBitsize(), basesize = bitsize % BBS;
    std::cout << bitsize << std::endl;
    std::cout << basesize << std::endl;
    v = NULL;
}

LONG bf:: getBitsize() {
    return (LONG)(1 << n);
}
