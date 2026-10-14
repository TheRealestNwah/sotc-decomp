typedef int s128 __attribute__((mode(TI)));
typedef struct { long lo, hi; } Mvec;
typedef union { Mvec m; s128 q; } MvecU;

void iosClampUW_AddMvec(s128 *dst, Mvec *a, Mvec *b)
{
    MvecU x;
    MvecU y;
    s128 r;
    x.m = *a;
    y.m = *b;
    __asm__ __volatile__("padduw %0, %1, %2" : "=r"(r) : "r"(x.q), "r"(y.q));
    *dst = r;
}
