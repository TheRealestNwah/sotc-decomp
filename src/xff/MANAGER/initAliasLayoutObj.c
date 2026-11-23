/* Parked: 9 diffs, same size (205 words). Builds an alias layout-object definition: resolves the dld handles at def+4 / def+0xC, fills a 0x28-byte AliasDef in a temporary and struct-assigns it to the by-value argument of func_00082838 (this reproduces the Original's ldl/sdl block copy into the outgoing argument area), then calls CreateAliasScriptLayoutObj and adds the object to the D_00136C10 + 0x18 group when the def+8 handle resolved. Remaining: register allocation around the GetLayoutClass short load and the def+8 dld resolve (Original: a1 = def+8, a2 = handle, a0 = mask, lh into v1 after the and; ours: a2/a3/a0 with the lh scheduled earlier). One 30-minute permuter run found nothing better. */
extern int DldSysUndefSymbol;
extern int D_00136C10;
typedef struct {
    int w0;
    int w4;
    void *w8;
    void *wC;
    int w10;
    int w14;
    int w18;
    int w1C;
    int w20;
    int w24;
} AliasDef;

extern char *GetLayoutClass(void *);
extern void func_00082838(void *, void *, void *, void *, AliasDef, void *, int, void *, int, int);
extern void *CreateAliasScriptLayoutObj(void *, int, void *, void *);
extern int CheckLayoutObjChainExist(void *);
extern void isysAddGroupWithLinkParam(void *, int, int, int);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

#ifdef NONMATCHING
void *initAliasLayoutObj(void *owner, int *def, void *a2, int a3, void *layout, void *t1, int t2)
{
    AliasDef ad;
    AliasDef tmp;
    char buf[0xB0];
    char *r1;
    char *r2;
    int s7;
    int s3;
    void *obj;

    r1 = dldResolve((unsigned int *)(def + 1));
    s7 = 0;
    if (r1 != 0)
        s7 = *(int *)(r1 + 8);
    r2 = dldResolve((unsigned int *)(def + 3));
    s3 = 0;
    if (r2 != 0)
        s3 = *(int *)(r2 + 8);
    tmp.w4 = *(short *)(GetLayoutClass(layout) + 0x1B4);
    tmp.w0 = def[0];
    tmp.w8 = dldResolve((unsigned int *)(def + 2));
    tmp.wC = dldResolve((unsigned int *)(def + 4));
    tmp.w10 = 0;
    tmp.w14 = 0;
    tmp.w18 = a3;
    tmp.w1C = 0x1000;
    tmp.w20 = 0;
    tmp.w24 = 0;
    ad = tmp;
    func_00082838(buf, (void *)s7, (void *)s3, owner, ad, a2, 0, t1, 0, t2);
    obj = CreateAliasScriptLayoutObj(owner, 0, buf, layout);
    if (obj != 0 && ad.w8 != 0 && CheckLayoutObjChainExist(obj) != 0)
        isysAddGroupWithLinkParam(obj, D_00136C10 + 0x18, 0, 0);
    return obj;
}
#else
extern void *initAliasLayoutObj(void *owner, int *def, void *a2, int a3, void *layout, void *t1, int t2);
#endif
