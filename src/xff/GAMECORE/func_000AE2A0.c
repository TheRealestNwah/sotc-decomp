typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern int *DldSysUndefSymbol;
extern void *isysGetThisSubThread(void);
extern char *GetLayoutClass(void *);
extern void SCRGetCharNodePos(float *, void *, int);

static inline char *dldResolve(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((*h >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static inline int dldCount(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? t[3] : 0;
}

typedef struct { unsigned int h; float r; } Ent;

static int func_000AE2A0(char *a)
{
    void *th = isysGetThisSubThread();
    unsigned int *h = (unsigned int *)(*(char **)(a + 0x20C) + 0x20);
    unsigned int v = *h;
    int *t;
    char *p;
    char *lay;
    int n;
    int i;

    t = (v & 0x3FFFF) != 0 ? *(int **)((char *)h - (v & 0x3FFFF)) : 0;
    if (t != 0 && t != DldSysUndefSymbol)
        p = (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3];
    else
        p = 0;
    lay = GetLayoutClass(th);
    n = 0;
    if (p != 0)
        n = dldCount((unsigned int *)(*(char **)(a + 0x20C) + 0x20));
    for (i = 0; i < n; i++) {
        float r = ((Ent *)p)[i].r;
        Vec4 pos;
        float d;

        SCRGetCharNodePos(pos.f, *(void **)(a + 0x44), (int)dldResolve(&((Ent *)p)[i].h));
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vsub.xyzw vf7, vf5, vf6\n"
                             "vmul.xyz vf7, vf7, vf7\n"
                             "vaddy.x vf7, vf7, vf7y\n"
                             "vaddz.x vf7, vf7, vf7z\n"
                             "qmfc2.ni $2, vf7\n"
                             "mtc1 $2, %0\n"
                             : "=f"(d) : "r"(pos.f), "r"(*(float **)(lay + 0x134)) : "$2");
        if (d < r * r)
            return 1;
    }
    return 0;
}
