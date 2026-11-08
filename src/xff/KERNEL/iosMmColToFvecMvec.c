typedef int s128 __attribute__((mode(TI)));
typedef union { long words[2]; int i[4]; s128 q; } IVector;
extern void iosITOF15Vector(float *, IVector *);

void iosMmColToFvecMvec(float *out, const IVector *in)
{
    IVector x;
    IVector r;
    IVector y;

    x = *in;
    y = x;
    __asm__ __volatile__("psrlw %0, %1, 8" : "=r"(r.q) : "r"(y.q));
    iosITOF15Vector(out, &r);
}
