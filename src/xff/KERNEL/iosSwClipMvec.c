typedef int s128 __attribute__((mode(TI)));
typedef struct { long lo, hi; } Mvec;
typedef union { Mvec m; s128 q; } MvecU;

void iosSwClipMvec(s128 *dst, Mvec *a, Mvec *lo, Mvec *hi)
{
    MvecU x;
    MvecU y;
    MvecU z;
    s128 r;
    x.m = *a;
    y.m = *lo;
    z.m = *hi;
    __asm__ __volatile__("pceqw $8, $0, $0\n"
                         "psrlw $9, $8, 1\n"
                         "psrlw $10, $8, 31\n"
                         "paddw $10, $9, $10\n"
                         "psubsw %0, %1, %2\n"
                         "paddsw %0, %0, $9\n"
                         "psubsw %0, %0, $9\n"
                         "paddsw %0, %0, %2\n"
                         "psubsw %0, %0, %3\n"
                         "paddsw %0, %0, $10\n"
                         "psubsw %0, %0, $10\n"
                         "paddsw %0, %0, %3\n"
                         : "=r"(r) : "0"(x.q), "r"(y.q), "r"(z.q) : "$8", "$9", "$10");
    *dst = r;
}
