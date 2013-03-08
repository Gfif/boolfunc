#include"stdio.h"
#include"iostream"
#define BASE unsigned long 
#define BBS 64
#define LONG unsigned long
class bf {
    private:
        BASE *v;
        unsigned long n;
   public:
        bf(LONG = 0);
        LONG getBitsize();
};
