extern int DldSysUndefSymbol;
extern char B_00188610[];
extern int *isysGroupForFirst(void *, int);
extern int *isysGroupForNext(int *, int);
extern void isysGroupForExit(void *, int);
extern void isysRequestDeleteObj(void *, int);
extern char *GetLayoutClass(void *);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

typedef struct {
    int pad;
    unsigned int ref;
    int pad2;
} SlowEntry;

void deleteSlowObject(char *w)
{
    int n = *(int *)(w + 0xC);
    SlowEntry *e = *(SlowEntry **)(w + 0x10);
    int i;

    for (i = 0; i < n; i++, e++) {
        char *p = dldResolve(&e->ref);
        int key = *(int *)(dldResolve((unsigned int *)(p + 4)) + 8);
        void *o = 0;
        int *g;

        for (g = isysGroupForFirst(B_00188610, 0); g != 0; g = isysGroupForNext(g, 0)) {
            o = (void *)*g;
            if (key == **(int **)(GetLayoutClass(o) + 0x144)) {
                isysRequestDeleteObj(o, 0);
                break;
            }
        }
        if (o != 0)
            isysGroupForExit(o, 0);
    }
}
