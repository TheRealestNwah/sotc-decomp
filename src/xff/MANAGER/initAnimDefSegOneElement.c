extern int DldSysUndefSymbol;
extern char rootPtn[];
extern int D_00136C10;
extern void *CreateAnimationDefObj(void *, int, void *);
extern void isysAddGroupWithLinkParam(void *, int, int, int);

typedef struct { char pad0[0xC]; int size; } DldType;
typedef struct { char pad0[8]; DldType *type; char padC[4]; char *data; } DldTable;

typedef struct Seg {
    char pad0[4];
    int link;
    char pad8[0x64];
    void *obj;
} Seg;

static inline DldTable *dldTable(int *h, unsigned int v)
{
    int off = v & 0x3FFFF;
    return off != 0 ? *(DldTable **)((char *)h - off) : 0;
}

static inline void *dldElement(int *h, unsigned int v)
{
    DldTable *t = dldTable(h, v);
    return (t != 0 && t != (DldTable *)DldSysUndefSymbol) ? t->data + ((v >> 18) & 0xFFF) * t->type->size : 0;
}

void *initAnimDefSegOneElement(Seg *s)
{
    void *obj;
    int def;
    int arg[2];
    char *e;
    unsigned int v;
    int *h;

    if (s->obj == 0) {
        h = &s->link;
        v = *h;
        if (dldTable(h, v) != 0 && dldTable(h, v) != (DldTable *)DldSysUndefSymbol) {
            e = dldElement(h, v);
            def = 0;
            if (e != 0)
                def = *(int *)(e + 8);
            if (def != 0) {
                arg[0] = def;
                arg[1] = (int)s;
                obj = CreateAnimationDefObj(rootPtn, 0, arg);
                s->obj = obj;
                if (obj != 0) {
                    isysAddGroupWithLinkParam(obj, D_00136C10 + 8, 0, 0);
                    return obj;
                }
            }
        }
        s->obj = 0;
        return 0;
    }
    return s->obj;
}
