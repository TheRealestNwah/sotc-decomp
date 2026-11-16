extern int DldSysUndefSymbol;
extern int getEditWorkInitData(int);

typedef struct {
    float v[4];
    int a;
    int b;
    int pad[2];
} Slot;

typedef struct {
    int zero;
    int pad4[3];
    Slot slot[7];
    float f0;
    int count;
    int ref;
    float f1;
    float f2;
    float f3;
    float f4;
    float f5;
    int pad110;
    int r114;
    int pad118[2];
    int z120;
    int z124;
    int pad128[2];
    float tail[4];
    int pad140[4];
    int z150;
} EditWork;

static inline char *dldData(unsigned int *h)
{
    unsigned int enc = *h;
    unsigned int off = enc & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    if (t != 0 && t != (char *)DldSysUndefSymbol)
        return *(char **)(t + 0x10) + ((enc >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC);
    return 0;
}

static inline int dldRef(unsigned int *h)
{
    unsigned int enc = *h;
    register unsigned int m __asm__("$2");
    unsigned int off;
    char *t;

    __asm__ __volatile__("" : : "r"(enc));
    m = 0x3FFFF;
    off = enc & m;
    t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(int *)(t + 0xC) : 0;
}

static void func_00052EA8(EditWork *w, char *obj)
{
    char *p = *(char **)(obj + 0x1C);
    char *d = dldData((unsigned int *)(p + 0x1C));
    int i;
    int r;
    char *q;
    char *sp;
    int *zp;

    r = getEditWorkInitData(*(int *)(p + 8));
    w->zero = 0;
    sp = (char *)w + 0x10;
    for (i = 6; i >= 0; i--) {
        __asm__ __volatile__("sqc2 vf0, 0x0(%0)
" : : "r"(sp) : "memory");
        *(int *)(sp + 0x10) = 0;
        *(int *)(sp + 0x14) = 0;
        sp += 0x20;
    }
    q = *(char **)(obj + 0x1C);
    w->count = *(int *)(q + 0x30) != 0 ? *(int *)(q + 0x3C) : *(int *)(q + 0x28) * *(int *)(q + 0x2C);
    w->ref = dldRef((unsigned int *)d);
    w->f2 = 1.5f;
    w->f1 = 0.5f;
    w->f0 = *(float *)(d + 0x10);
    w->f3 = 0.1f;
    w->f4 = 0.5f;
    w->f5 = 1.0f;
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(&w->tail) : "memory");
    w->r114 = r;
    zp = (int *)((char *)w + 0x120);
    zp[0] = 0;
    zp[1] = 0;
    zp[0] = *(int *)(d + 8);
    w->z150 = 0;
}
