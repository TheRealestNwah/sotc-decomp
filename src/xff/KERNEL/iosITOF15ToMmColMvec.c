typedef int s128 __attribute__((mode(TI)));
typedef struct {
    long lo, hi;
} Mvec;

void iosITOF15ToMmColMvec(s128 *dst, Mvec *src)
{
    s128 t;

    *(Mvec *)&t = *src;
    __asm__("psllw %0, %1, 8" : "=r"(t) : "r"(t));
    *dst = t;
}
