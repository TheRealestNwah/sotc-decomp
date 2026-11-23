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
typedef struct {
    int w0;
    int w4;
    void *w8;
    void *wC;
    void *w10;
    int w14;
    int w18;
    int w1C;
    void *w20;
    int w24;
} AliasDef;
typedef struct { char b[0xB0]; } LayoutDef;
typedef struct {
    int w0, w4, w8, wC, w10, w14, w18, w1C, w20, w24, w28, w2C;
    char w30[1];
} ScriptDef;

extern void func_00082838(void *, void *, void *, void *, AliasDef, void *, int, int, int, int);
extern void *CreateScriptLayoutObj(void *, int, void *);
extern int CheckLayoutObjChainExist(void *);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);

void *initScriptLayoutObj(void *owner, ScriptDef *def, void *a2, int a3, int t0, int t1, int t2)
{
    AliasDef ad;
    AliasDef tmp;
    char buf[0xB0];
    void *r1;
    void *r2;
    char *e;
    void *obj;

    e = dldElement(&def->w8);
    r1 = e != 0 ? *(void **)(e + 8) : 0;
    e = dldElement(&def->w10);
    r2 = e != 0 ? *(void **)(e + 8) : 0;
    tmp.w0 = def->w0;
    tmp.w4 = 1;
    tmp.w8 = dldElement(&def->wC);
    tmp.wC = dldElement(&def->w14);
    tmp.w10 = dldElement(&def->w2C) != 0 ? &def->w2C : 0;
    tmp.w14 = def->w28;
    tmp.w18 = def->w1C;
    tmp.w1C = def->w20;
    tmp.w20 = def->w30;
    tmp.w24 = def->w18;
    ad = tmp;
    func_00082838(buf, r1, r2, owner, ad, a2, a3, t0, t1, t2);
    obj = CreateScriptLayoutObj(owner, 0, buf);
    if (obj != 0) {
        if (ad.w8 != 0 && CheckLayoutObjChainExist(obj) != 0)
            isysAddGroupWithLinkParam(obj, D_00136C10 + 0x18, 0, 0);
        if (dldElement(&def->w2C) != 0) {
            char *base = D_00136C10 + 0x1C;
            char *dp = dldElement(&def->w2C);
            char *link = base + 4;
            int *slot = (int *)(dp + 0x34);
            int i;
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
