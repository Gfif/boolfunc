#include"stdio.h"
#include"stdlib.h"
#include"iostream"
#include"string"
#define BASE unsigned int 
#define BBS 32 
#define LOGBBS 5
#define MASK1 0xaaaaaaaa
#define MASK2 0xcccccccc
#define MASK3 0xf0f0f0f0
#define MASK4 0xff00ff00
#define MASK5 0xffff0000
#define LONG long int
#define ULONG unsigned long
#define UINT unsigned int
#define UCHAR unsigned char
class bf {
    private:
        BASE *v;
        UCHAR n;
   public:
        bf(UCHAR = 0, UCHAR = 0);
        bf(std::string &);
        bf(const bf&);
        ~bf() {delete []v; v = NULL;}
        UINT getBitSize() const;
        UINT getBaseSize() const;
        UCHAR getValue(BASE) const;
        UCHAR getN() const;
        BASE weight() const;
        UCHAR cor() const;
        UCHAR PC() const;
        void setAll0();
        void setValue(BASE, UCHAR);
        void printHex();
        bf inv() const;
        bf u() const;
        bf operator =(const bf&);
        void anf() const;
        UCHAR deg() const;
        bf NAP() const;
        UCHAR Nf() const;
        UCHAR CNf() const;
        void walsh(LONG*) const;
        void autocor(LONG*) const;
        friend std::ostream& operator <<(std::ostream&, const bf&);
};
UCHAR baseweight(const BASE);
UCHAR log(BASE);
//UCHAR next(BASE, UCHAR, UCHAR);
