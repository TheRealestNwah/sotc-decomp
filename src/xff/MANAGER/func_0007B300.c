typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } QF;

typedef struct LightSrc {
    s128 q0;
    s128 q1;
    float f20;
    float f24;
    float rgb[3];
    signed char b34;
    char pad35[3];
    float f38;
    float f3C;
    float f40;
} LightSrc;

typedef struct LightDef {
    char pad0[0x10];
    LightSrc l;
} LightDef;

typedef struct Light {
    QF q0;
    QF q1;
    unsigned char c[4];
    float f24;
    float f28;
    unsigned int flags;
    int i30;
    float f34;
    unsigned char br;
    char pad39[3];
    int col;
    float f40;
    float f44;
    float f48;
    float f4C;
    char pad50[4];
    void (*fn)(struct Light *);
} Light;

typedef struct Arg { int type; int i4; int *pp; } Arg;

extern unsigned char iosCalcIcolorToBrightness(int);
extern int IsFullFixFormat(int);

static int func_0007B300(Light *o, Arg *a, LightDef *d)
{
    LightSrc *p1 = 0;
    LightSrc *p2 = 0;
    float f;

    o->flags = 0;
    switch (a->type) {
    case 27:
        p2 = &d->l;
        o->flags |= 2;
        break;
    case 28:
        p2 = &d->l;
        o->flags |= 1;
        break;
    case 33:
        p1 = &d->l;
        o->flags |= 4;
        break;
    case 34:
        p1 = &d->l;
        o->flags |= 8;
        break;
    case 35:
        p1 = &d->l;
        o->flags |= 0x10;
        break;
    }
    o->i30 = a->i4;
    if (p1 != 0) {
        o->q0.q = p1->q0;
        o->q1.q = p1->q1;
        o->c[0] = (unsigned int)p1->rgb[0];
        o->c[1] = (unsigned int)p1->rgb[1];
        o->c[2] = (unsigned int)p1->rgb[2];
        o->c[3] = 0xFF;
        o->f24 = p1->f20;
        o->f28 = p1->f24;
        o->f44 = p1->f3C;
        o->f48 = p1->f38;
        o->f4C = p1->f40 * p1->f40;
    } else {
        o->q0.q = p2->q0;
        o->q1.q = p2->q1;
        o->c[0] = (unsigned int)p2->rgb[0];
        o->c[1] = (unsigned int)p2->rgb[1];
        o->c[2] = (unsigned int)p2->rgb[2];
        o->c[3] = 0xFF;
        o->f24 = p2->f20;
        o->f28 = p2->f24;
    }
    if (o->fn != 0)
        o->fn(o);
    o->col = *(int *)o->c;
    o->br = iosCalcIcolorToBrightness(o->col);
    f = (float)o->br * o->f24;
    if (f < 0.0f)
        f = -f;
    o->f40 = f;
    o->f34 = o->f28 * o->f28;
    if (p1 != 0) {
        if (p1->b34)
            o->flags |= 0x100;
        if (!IsFullFixFormat(*a->pp))
            o->flags |= 0x20000;
        else
            o->flags |= 0x10000;
    } else {
        if (p2->b34)
            o->flags |= 0x100;
        if (!IsFullFixFormat(*a->pp))
            o->flags |= 0x20000;
        else
            o->flags |= 0x10000;
    }
    return 1;
}
