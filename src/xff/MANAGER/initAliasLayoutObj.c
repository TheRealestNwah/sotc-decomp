/* ~92 diffs, 21 words short (184 vs 205). Builds an alias layout-object definition (initAliasLayoutObj, lowercase variant; the capitalised InitAliasScriptLayoutObj calls the matched InitAliasLayoutObj): resolves the dld handles at def+4 / def+0xC (module-size words at +8), then fills a 0x28-byte AliasDef (def[0], the short at layout+0x1B4, resolved def+8 / def+0x10, 0x1000 at +0x1C, ...), passes it by value to func_00082838 together with a 0xB0 scratch buffer, calls CreateAliasScriptLayoutObj(owner, 0, buf, layout) and, when the def+8 handle resolved and CheckLayoutObjChainExist, adds the object to the group at D_00136C10 + 0x18. Remaining diff: the Original builds the struct in a local at sp+0x40 and copies it into the outgoing argument area with ldl/ldr/sdl/sdr pairs (then reads the def+8 pointer back from the argument slot after the call), ours constructs it straight in the argument slot and so omits the copy. */
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
    struct { AliasDef a; AliasDef pad; char buf[0xB0]; } L;
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
    L.a.w0 = def[0];
    L.a.w4 = *(short *)(GetLayoutClass(layout) + 0x1B4);
    L.a.w8 = dldResolve((unsigned int *)(def + 2));
    L.a.wC = dldResolve((unsigned int *)(def + 4));
    L.a.w10 = 0;
    L.a.w14 = 0;
    L.a.w18 = a3;
    L.a.w1C = 0x1000;
    L.a.w20 = 0;
    L.a.w24 = 0;
    func_00082838(L.buf, (void *)s7, (void *)s3, owner, L.a, a2, 0, t1, 0, t2);
    obj = CreateAliasScriptLayoutObj(owner, 0, L.buf, layout);
    if (obj != 0 && L.a.w8 != 0 && CheckLayoutObjChainExist(obj) != 0)
        isysAddGroupWithLinkParam(obj, D_00136C10 + 0x18, 0, 0);
    return obj;
}
#endif
