#include "bf.h"


UCHAR baseweight(const BASE y) {
    BASE w = 0;
    BASE x = y;
    x = (x & ~MASK1) + ((x >> 1) & ~MASK1);
    x = (x & ~MASK2) + ((x >> 2) & ~MASK2);
    x = (x + (x >> 4)) & ~MASK3;
    x += (x >> 8);
    x += (x >> 16);
    return (BASE)(x & 0x3f);
}

UCHAR log(BASE b) {
    UCHAR k = 0;
    for ( ; b != 0; b >>= 1, ++k);
    return k - 1;
}

UCHAR next(BASE &b, UCHAR n, UCHAR k) {
    BASE d = (1 << k) - 1;
    if (b == d) {
        return 1;
    }
    BASE c = (b + 1) & b;
    UCHAR w = baseweight((c - 1) ^ b) - 2;
    b = (((((b + 1) ^ b) << 1) + 1) << w) ^ c;
    return 0;
}

LONG max(LONG* a, BASE n) {
    BASE m = abs(a[0]);
    for (BASE arg = 1; arg < n; arg++) {
        if (abs(a[arg]) > m) {
            m = abs(a[arg]);
        }
    }
    return m;
}

BASE amax(LONG* a, BASE n) {
    BASE argmax = 0;
    for (BASE arg = 1; arg < n; arg++) {
        if (abs(a[arg]) > abs(a[argmax])) {
            argmax = arg;
        }
    }
    return argmax;
}

void green(LONG* a, UCHAR n) {
    UINT maxstep = (1 << (n - 1)); 
    for (UINT step = 1; step <= maxstep; step <<= 1) {
        UINT n2 = (1 << n);
        UINT dubstep = step << 1;
        for (UINT i = 0; i < n2; i += dubstep) {
            for (UINT j = 0; j < step; j++) {
                LONG plus = a[i + j] + a[i + j + step];
                LONG minus = a[i + j] - a[i + j + step];
                a[i + j] = plus;
                a[i + j + step] = minus;
            }
        }
    }
}

/* Constructor
*    size - numbers of variables
*    rnd - flag.
*    Default values 0, 0.
*    If rnd == 1 then generate random bool function. */
bf:: bf(UCHAR size, UCHAR rnd) {
    n = size;
    BASE bitsize = getBitSize(), basesize = (bitsize - 1) / BBS + 1;
    v = new BASE [basesize];
    if (rnd) {
        for (int i = 0; i < basesize; i++) {
            *(v + i) = rand() - rand();
        }
    }
    else {
        setAll0();
    }
    if (LOGBBS > n) {
        BASE mask = (1 << (1 << n)) - 1;
        *v &= mask;
    }
    
}

bf:: bf(std::string& s) {
    BASE len = s.length();
    if (baseweight(len) != 1) {
        std::cout << "Error" << std::endl;
        n = 0;
        v = NULL;
    }
    else {
        bf res(log(len));
        for (BASE i = 0; i < len; ++i) {
            res.setValue(i, s[i] - '0');
        }
        BASE basesize = res.getBaseSize();
        n = res.n;
        v = new BASE [basesize];
        for (BASE i = 0; i < basesize; i++) {
            v[i] = res.v[i];
        }
    }
}
        
/* copy constructor */
bf:: bf(const bf& a) {
    n = a.n;
    BASE bitsize = getBitSize(), basesize = (bitsize - 1) / BBS + 1;
    v = new BASE [basesize];
    for (BASE i = 0; i < basesize; i++) {
        v[i] = a.v[i];
    }
}

/* This function returns size of boolean vector in bits. */
BASE bf:: getBitSize() const {
    return (BASE)(1 << n);
}

/* This function returns size of boolean vector in bases. */
BASE bf:: getBaseSize() const {
    return (BASE)((getBitSize() - 1) / BBS + 1);
}

/* Returns n. */
UCHAR bf:: getN() const {
    return n;
}

bf bf:: inv() const{
    bf res(n);
    BASE basesize = res.getBaseSize();
    for (BASE i = 0; i < basesize; i++) {
        *(res.v + i) = ~(*(v + i));
    }
    if (LOGBBS > n) {
        BASE mask = (1 << (1 << n)) - 1;
        *res.v &= mask;
    }
    return res;
}


/* This function set all bits to 0 */
void bf:: setAll0() {
    BASE basesize = getBaseSize();
    for (int i = 0; i < basesize; i++) {
        *(v + i) = 0;
    }
}

void bf:: setValue(BASE position, UCHAR value) {
    BASE valuebase = position / BBS;
    BASE valuebit = position % BBS;
    BASE mask = 1 << valuebit;
    if (value) {
        v[valuebase] |= mask;
    }
    else {
        v[valuebase] = ~((~v[valuebase]) | (mask));
    }
}

/* getValue returns boolean function value f(x)
 * where x is n-ary boolean vector. */
UCHAR bf:: getValue(BASE x) const {
    BASE valuebase = x / BBS;
    BASE valuebit = x % BBS;
    BASE mask = 1 << valuebit;

    return (UCHAR) !!(mask & v[valuebase]); 
}

/* print boolean vector to stdout */
std::ostream& operator << (std::ostream& out, const bf& a) {
    BASE bitsize = a.getBitSize(), basesize = a.getBaseSize();
    char* s = new char[bitsize + 1];
    if (NULL == s) {
        std::cerr << "It's to big" << std::endl;
        return out;
    }
    s[bitsize] = 0;
    BASE mask, k = 0;
    for (BASE i = 0; i < basesize; i++) {
        mask = 1;
        while(mask && k < bitsize) {
            s[k] = (!!(mask & a.v[i])) + '0';
            k++;
            mask <<= 1;
        }
    }
    out << s;
    delete []s;
    return out;
}

/* prints boolean vector in hex
 * just for debug */
void bf:: printHex() {
    BASE basesize = getBaseSize();
    for (BASE i = 0; i < basesize; i++) {
        std::cout << std::hex << v[i] << std::endl;
    }
}

BASE bf:: weight() const {
    BASE basesize = getBaseSize();
    BASE w = 0;
    for (BASE* i = v; i < v + basesize; i++) {
        BASE x = *i;
        x = (x & ~MASK1) + ((x >> 1) & ~MASK1);
        x = (x & ~MASK2) + ((x >> 2) & ~MASK2);
        x = (x + (x >> 4)) & ~MASK3;
        x += (x >> 8);
        x += (x >> 16);
        w += (x & 0x3f);
    }
    return w;
}

/* Mobius transformation */
bf bf:: u() const {
    bf g = *this;
    BASE basesize = getBaseSize();
    for (BASE i = 0; i < basesize; i++) {
        g.v[i] = g.v[i] ^ ((g.v[i] << 1) & MASK1);
        g.v[i] = g.v[i] ^ ((g.v[i] << 2) & MASK2);
        g.v[i] = g.v[i] ^ ((g.v[i] << 4) & MASK3);
        g.v[i] = g.v[i] ^ ((g.v[i] << 8) & MASK4);
        g.v[i] = g.v[i] ^ ((g.v[i] << 16) & MASK5);
    }
    for (BASE t = 1; t < basesize; t <<= 1) {
        for (BASE i = 0; i < basesize; i += (t << 1)) {
            for (BASE j = i; j < i + t; j++) {
                g.v[j + t] ^= g.v[j];
            }
        }
    }
    if (LOGBBS > n) {
        BASE mask = (1 << (1 << n)) - 1;
        *v &= mask;
    }
    return g;
}

bf bf:: operator =(const bf& a) {
    if (&a == this) {
        return *this;
    }
    delete []v;
    n = a.n;
    BASE bitsize = a.getBitSize(), basesize = (bitsize - 1) / BBS + 1;
    v = new BASE [basesize];
    for (BASE i = 0; i < basesize; i++) {
        v[i] = a.v[i];
    }
    return *this;
}

void bf:: anf() const {
    bf g = u();
    char *s;
    s = new char[200000];
    ULONG ssize = 0;
    BASE maxvalue = (1 << n) - 1;
    if (g.getValue(0)) {
        s[ssize] = '1';
        s[ssize + 1] = ' ';
        s[ssize + 2] = '+';
        s[ssize + 3] = ' ';
        ssize += 4;
    }
    for (BASE i = 1; i <= maxvalue; i++) {
        if (g.getValue(i)) {
            BASE mask = 1;
            UCHAR k = 1;
            while (mask < maxvalue) {
                if (mask & i) {
                    s[ssize] = 'x';
                    if (k < 10) {
                        s[ssize + 1] = '0' + k;
                        s[ssize + 2] = '*';
                        ssize += 3;
                    }
                    else {
                        s[ssize + 1] = '0' + (k / 10);
                        s[ssize + 2] = '0' + (k % 10);
                        s[ssize + 3] = '*';
                        ssize += 4;
                    }
                }
                mask <<= 1;
                k++;
            }
            s[ssize - 1] = ' ';
            s[ssize] = '+';
            s[ssize + 1] = ' ';
            ssize += 2;
        }
    }
    s[ssize - 3] = 0;
    std::cout << s << std::endl;
    delete []s;
}

UCHAR bf:: deg() const {
    bf g = u();
    BASE maxvalue = (1 << n) - 1;
    UCHAR deg = 0;
    if (g.getValue(maxvalue)) {
        return n;
    }
    for (BASE i = 1; i <= maxvalue; i++) {
        if (g.getValue(i) & deg < baseweight(i)) {
            deg = baseweight(i);
        }
    }
    return deg;
}

void bf:: walsh(LONG* a) const {
    BASE maxvalue = (1 << n) - 1;
    for (BASE i = 0; i <= maxvalue; i++) {
        if (getValue(i)) {
            a[i] = -1;
        } else {
            a[i] = 1;
        }
    }
    /*
    UINT maxstep = (1 << (n - 1)); 
    for (UINT step = 1; step <= maxstep; step <<= 1) {
        UINT n2 = (1 << n);
        UINT dubstep = step << 1;
        for (UINT i = 0; i < n2; i += dubstep) {
            for (UINT j = 0; j < step; j++) {
                LONG plus = a[i + j] + a[i + j + step];
                LONG minus = a[i + j] - a[i + j + step];
                a[i + j] = plus;
                a[i + j + step] = minus;
            }
        }
    }
    */
    green(a, n);
}

UCHAR bf:: cor() const{
    LONG* a = new LONG [(1 << n)];
    walsh(a);
    for (UCHAR m = 1; m <= n; m++) {
        UCHAR f = 0;
        for (BASE b = ((1 << m) - 1) << (n - m); !f; f = next(b, n, m) ) {
            //std::cout << std::hex << b << std::endl;
            if (a[b] != 0)
                return m - 1;
        }
    }
    return n;
}

bf bf:: NAP() const{
    BASE bitsize = getBitSize();
    LONG *a = new LONG [bitsize];
    bf res(n);
    walsh(a);
    BASE arg = amax(a, bitsize);
    BASE mask;
    UCHAR i;
    for (mask = 1, i = 0; i < n; mask <<= 1, i++) {
        if (mask & arg) {
            res.setValue((BASE)(1 << i), 1);
        }
    }
    res = res.u();
    if (a[arg] < 0) {
        delete [] a;
        return res.inv();
    }
    delete [] a;
    return res;
}

UCHAR bf:: Nf() const{
    BASE bitsize = getBitSize();
    LONG *a = new LONG [bitsize];
    walsh(a);
    UCHAR res = (1 << (n - 1)) - (max(a, bitsize) >> 1);
    delete [] a;
    return res;
}

void bf:: autocor(LONG* a) const{
    BASE bitsize = getBitSize();
    walsh(a);
    for (BASE i = 0; i < bitsize; i++) {
        a[i] *= a[i];
    }
    green(a, n);
    for (BASE i = 0; i < bitsize; i++) {
        a[i] >>= n;
    }
}

UCHAR bf:: PC() const{
    LONG* a = new LONG [(1 << n)];
    autocor(a);
    for (UCHAR m = 1; m < n; m++) {
        UCHAR f = 0;
        for (BASE b = ((1 << m) - 1) << (n - m); !f; f = next(b, n, m) ) {
            if (a[b] != 0)
                return m - 1;
        }
    }
    return n;
}

UCHAR bf:: CNf() const{
    BASE bitsize = getBitSize();
    LONG *a = new LONG [bitsize];
    autocor(a);
    UCHAR res = (1 << (n - 2)) - (max(a, bitsize) >> 2);
    delete [] a;
    return res;
}
