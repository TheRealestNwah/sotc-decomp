typedef int s128 __attribute__((mode(TI)));
typedef struct { long lo, hi; } Mvec;
typedef union { Mvec m; s128 q; } MvecU;
extern void iosFTOI15Vector(Mvec *, void *);

void iosFvecToMmColMvec(Mvec *dst, void *src)
{
    MvecU x;
    s128 r;
    iosFTOI15Vector(dst, src);
    x.m = *dst;
    __asm__ __volatile__("psllw %0, %1, 8" : "=r"(r) : "r"(x.q));
    *(s128 *)dst = r;
}
