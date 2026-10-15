typedef int s128 __attribute__((mode(TI)));
typedef struct { unsigned int r : 8; unsigned int g : 8; unsigned int b : 8; unsigned int a : 8; } Col;
typedef union { Col c; int i; s128 q; } ColU;

void iosIColAddVecXYZ(int *out, int col, int r, int g, int b)
{
    ColU x;
    ColU y;
    ColU z;
    Col t;
    t.r = r;
    t.g = g;
    t.b = b;
    t.a = 0xFF;
    x.i = col;
    y.c = t;
    __asm__ __volatile__("paddub %0, %1, %2" : "=r"(z.q) : "r"(x.q), "r"(y.q));
    *out = z.i;
}
