extern int DldSysUndefSymbol;
extern char *GetSCRCharaAIWorkPtr(void *chr);
extern int stagemanager_checkstageAlreadyLoadRequestedByStrptr(unsigned int *s);
extern void stagemanager_unloadstageByStrptr(unsigned int *s);
extern void deleteUserPathWork(char *w);
extern void deleteGazeCtrlWork(char *w);

typedef void (*AIInitFn)(void *, int, int, float, float, float, float, long long, long long, int *, int *, int *, int *);

typedef struct {
    AIInitFn fn;
    int a;
    int b;
    float f0;
    float f1;
    float f2;
    float f3;
    int pad1C;
    long long c;
    long long d;
    int p30;
    int p34;
    int p38;
    int p3C;
} AIInitEnt;

static inline char *dldA(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

static inline int dldRef(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    return off != 0 ? *(int *)((char *)h - off) : 0;
}

static void func_0011BDF8(void *chr)
{
    char *w = (char *)(((int)GetSCRCharaAIWorkPtr(chr) + 0x13) & ~0xF);
    AIInitEnt *e = (AIInitEnt *)dldA(*(unsigned int **)(w + 0x4174));
    unsigned int *s;

    if (e != 0) {
        for (; e->fn != 0; e++) {
            AIInitFn fn = e->fn;
            fn(chr, e->a, e->b, e->f0, e->f1, e->f2, e->f3, e->c, e->d, &e->p30, &e->p34, &e->p38, &e->p3C);
        }
    }
    s = (unsigned int *)dldA(*(unsigned int **)(w + 0x417C));
    if (s != 0 && dldRef(s) != 0) {
        while (dldRef(s) != 0) {
            if (stagemanager_checkstageAlreadyLoadRequestedByStrptr(s)) {
                stagemanager_unloadstageByStrptr(s);
            }
            s++;
        }
    }
    deleteUserPathWork(w);
    deleteGazeCtrlWork(w + 0x3CC0);
}
