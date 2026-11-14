#ifdef NONMATCHING
/* Parked: 3 diffs, same as initLayoutObj (t0 = D_00136C10 + 0x1C before the second handle resolve, then s1 = t0 + 4). */
extern int DldSysUndefSymbol;
extern char *D_00136C10;
typedef struct { char pad0[0xC]; int size; } DldType;
typedef struct { char pad0[8]; DldType *type; char padC[4]; char *data; } DldTable;
static inline void *dldElement(int *h)
{
    int off = *h & 0x3FFFF;
    DldTable *t = off != 0 ? *(DldTable **)((char *)h - off) : 0;
    return (t != 0 && t != (DldTable *)DldSysUndefSymbol) ? t->data + (((unsigned int)*h >> 18) & 0xFFF) * t->type->size : 0;
}
extern void setLayoutClassInitParam(void *, int, int, void *, int);
extern int CreateLayoutObjVU0Secure(int, int, void *);
extern int CheckLayoutObjChainExist(int);
extern void isysAddGroupWithLinkParam(int, void *, int, int);

int initLayoutObjVU0Secure(int a0, int a1, char *a2, int a3)
{
    char param[0x80] __attribute__((aligned(16)));
    int obj;
    int i;
    char *link;
    int *slot;

    setLayoutClassInitParam(param, a0, a1, a2, a3);
    obj = CreateLayoutObjVU0Secure(a1, 0, param);
    if (obj != 0) {
        if (*(int *)(param + 0xC) != 0 && CheckLayoutObjChainExist(obj) != 0)
            isysAddGroupWithLinkParam(obj, D_00136C10 + 0x18, 0, 0);
        if (a2 != 0 && dldElement((int *)(a2 + 0x14)) != 0) {
            link = D_00136C10 + 0x1C;
            slot = (int *)((char *)dldElement((int *)(a2 + 0x14)) + 0x34);
            link += 4;
            for (i = 0xF; i >= 0; i--) {
                int v = *slot++;
                if (v != 0)
                    isysAddGroupWithLinkParam(obj, link, 0, 0);
                link += 4;
            }
        }
    }
    return obj;
}
#else
extern int initLayoutObjVU0Secure(int, int, char *, int);
#endif
