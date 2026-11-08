typedef int s128 __attribute__((mode(TI)));
typedef struct { unsigned char r, g, b, a; } __attribute__((aligned(4))) Col;
typedef union { Col c; int i; s128 q; } ColU;

void iosUcharColClampAdd(unsigned char *r, unsigned char *g, unsigned char *b, int ar, int ag, int ab)
{
    ColU x;
    ColU y;
    ColU z;
    ColU w;
    Col cx;
    Col cy;

    cx.r = *r;
    cy.r = ar;
    cx.g = *g;
    cy.g = ag;
    cx.b = *b;
    cy.b = ab;
    cx.a = 0xFF;
    cy.a = 0xFF;
    x.c = cx;
    y.c = cy;
    __asm__ __volatile__("paddub %0, %1, %2" : "=r"(z.q) : "r"(x.q), "r"(y.q));
    w.i = z.i;
    *r = w.c.r;
    *g = w.c.g;
    *b = w.c.b;
}
