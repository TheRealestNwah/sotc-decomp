extern int DldSysUndefSymbol;
extern char rootPtn[];
extern char *D_00136C10;
extern void *CreateScriptLwsOrientDefObj(void *, int, void *);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);

typedef struct DldType {
    char pad[0xC];
    int size;
} DldType;

typedef struct DldTable {
    char pad[8];
    DldType *type;
    int count;
    char *data;
} DldTable;

static inline DldTable *dldTable(unsigned int *h)
{
    unsigned int off = *h & 0x3FFFF;
    DldTable *t = off != 0 ? *(DldTable **)((char *)h - off) : 0;
    return (t != 0 && t != (DldTable *)DldSysUndefSymbol) ? t : 0;
}

static inline char *dldData(unsigned int *h)
{
    unsigned int off = *h & 0x3FFFF;
    DldTable *t = off != 0 ? *(DldTable **)((char *)h - off) : 0;
    return (t != 0 && t != (DldTable *)DldSysUndefSymbol) ? t->data : 0;
}

static inline int dldCount(unsigned int *h)
{
    unsigned int off = *h & 0x3FFFF;
    DldTable *t = off != 0 ? *(DldTable **)((char *)h - off) : 0;
    return (t != 0 && t != (DldTable *)DldSysUndefSymbol) ? t->count : 0;
}

static inline char *dldElement(unsigned int *h)
{
    unsigned int off = *h & 0x3FFFF;
    DldTable *t = off != 0 ? *(DldTable **)((char *)h - off) : 0;
    return (t != 0 && t != (DldTable *)DldSysUndefSymbol) ? t->data + ((*h >> 18) & 0xFFF) * t->type->size : 0;
}

typedef struct {
    int def;
    char *entry;
    char *seg;
} OrientParam;

static void func_00081D08(char *seg)
{
    char *entry = 0;
    int def = 0;
    int count = 0;
    char *e;
    char *f;
    int i;

    if (*(unsigned int *)(seg + 0x10) & 0x3FFFF) {
        entry = dldData((unsigned int *)(seg + 0x10));
        count = dldCount((unsigned int *)(seg + 0x10));
    }
    e = dldElement((unsigned int *)(seg + 4));
    if (e != 0) {
        f = dldElement((unsigned int *)(seg + 8));
        if (f == 0)
            f = dldElement((unsigned int *)(e + 0xDC));
        if (f != 0) {
            char *g = dldElement((unsigned int *)(f + 0x50));
            def = g != 0 ? *(int *)(g + 8) : 0;
        }
    }
    if (def == 0)
        return;
    for (i = 0; i < count; i++, entry += 0x2C) {
        OrientParam param = { def, entry, seg };
        void *o;
        if (*(void **)(entry + 0x28) != 0)
            continue;
        o = CreateScriptLwsOrientDefObj(rootPtn, 0, &param);
        if (o != 0) {
            isysAddGroupWithLinkParam(o, D_00136C10 + 8, 0, 0);
            *(void **)(entry + 0x28) = o;
        }
    }
}
