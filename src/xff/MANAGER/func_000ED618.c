/* Parked: 8 diffs, same size (477 words). Dispatches a Dld reference by
 * its definition type (SeList, RandomSE, SECondKind, PackageSE, EffKind,
 * RandomEffKind, PackageEFF, EffCondKind, ShockList, ScriptAnimationObjDef).
 * The two package loops, the shared 0x40-byte stack buffer (a TImode member
 * gives the lq/sq copy) and the reused `module` result in dldEntry2 fix most
 * of the layout.
 * Remaining: the EffKind entry's two failure branches are beql with the
 * zero in the delay slot in the Original (the zero block is out of line);
 * here they are beqz/bnel with the zero inline (6 words), and the
 * EffCondKind type test is bne rather than bnel. Pointer and int module
 * types, && / || / goto spellings and nested ifs all stayed at 8 or grew.
 * The permuter's base score is distorted on this static, so it was not
 * used. */
#ifdef NONMATCHING
typedef struct {
    float x, y, z, w;
} Vec4 __attribute__((aligned(16)));

extern int DldSysUndefSymbol;
extern char *SeList_dummy;
extern char _SeList[];
extern char _RandomSE[];
extern char _SECondKind[];
extern char _PackageSE[];
extern char _EffKind[];
extern char _RandomEffKind[];
extern char _PackageEFF[];
extern char _EffCondKind[];
extern char _ShockList[];
extern char _ScriptAnimationObjDef[];
extern char IdentityQuaternion[];
extern char ZeroPoint[];
extern int D_00139F78;
extern int D_00139F80;
extern int D_00139F84;
extern int D_00139F88;
typedef int s128 __attribute__((mode(TI)));
extern s128 B_0015E430;

extern void SetGeometryPointerNodePosState(void *, int, int, void *, void *);
extern void CopyGeometryPointer(void *, int);
extern int SequenceKickSE(char *, void *);
extern int func_000EC410(unsigned int *, void *);
extern int func_000EC698(unsigned int *, void *);
extern int func_000ECCF8(char *, void *);
extern unsigned int *func_000ED3C0(unsigned int *);
extern unsigned int *func_000ED160(unsigned int *);
extern void GetGeometryPointerPosition(Vec4 *, int);
extern void shockRequestCalcVol(char *, Vec4 *);
extern int kickLWS(char *, int, int, int, int, int);

static inline char *dldModule(unsigned int *reference)
{
    unsigned int offset = *reference & 0x3FFFF;
    char *module;

    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != (char *)DldSysUndefSymbol)
        return module;
    return 0;
}

static inline char *dldEntry(unsigned int *reference)
{
    unsigned int encoded = *reference;
    unsigned int offset = encoded & 0x3FFFF;
    char *module;

    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != (char *)DldSysUndefSymbol) {
        int index = (encoded >> 18) & 0xFFF;
        char *definition = *(char **)(module + 8);
        char *data = *(char **)(module + 0x10);
        return data + index * *(int *)(definition + 0xC);
    }
    return 0;
}

#define DLDTYPE(r) (*(char **)(dldModule(r) + 8))

static inline char *dldEntry2(unsigned int *reference)
{
    unsigned int encoded = *reference;
    unsigned int offset = encoded & 0x3FFFF;
    char *module;

    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module == 0 || module == (char *)DldSysUndefSymbol)
        module = 0;
    else
        module = *(char **)(module + 0x10) + ((encoded >> 18) & 0xFFF) * *(int *)(*(char **)(module + 8) + 0xC);
    return module;
}

static int func_000ED618(unsigned int *ref, void *ctx)
{
    union {
        char gp[0x40];
        Vec4 v;
        s128 q;
    } buf;

    if (DLDTYPE(ref) == _SeList) {
        char *se = dldEntry(ref);
        int ret = 0;
        if (se != SeList_dummy) {
            if (D_00139F80 == 0)
                SetGeometryPointerNodePosState(buf.gp, D_00139F78, 0, IdentityQuaternion, ZeroPoint);
            else
                CopyGeometryPointer(buf.gp, D_00139F80);
            ret = SequenceKickSE(se, buf.gp);
        }
        return ret;
    }
    if (DLDTYPE(ref) == _RandomSE)
        return func_000EC410(ref, ctx);
    if (DLDTYPE(ref) == _SECondKind)
        return func_000EC698(ref, ctx);
    if (DLDTYPE(ref) == _PackageSE) {
        unsigned int *list = (unsigned int *)dldEntry(ref);
        unsigned int *p = list;

        while (dldEntry(p))
            func_000ED618(p++, ctx);
        return 0;
    }
    if (DLDTYPE(ref) == _EffKind)
        return func_000ECCF8(dldEntry2(ref), ctx);
    if (DLDTYPE(ref) == _RandomEffKind)
        return func_000ED618(func_000ED3C0(ref), ctx);
    if (DLDTYPE(ref) == _PackageEFF) {
        unsigned int *list = (unsigned int *)dldEntry(ref);
        unsigned int *p = list;

        while (dldEntry(p))
            func_000ED618(p++, ctx);
        return 0;
    }
    if (DLDTYPE(ref) == _EffCondKind)
        return func_000ED618(func_000ED160(ref), ctx);
    if (DLDTYPE(ref) == _ShockList) {
        if (D_00139F80)
            GetGeometryPointerPosition(&buf.v, D_00139F80);
        else
            buf.q = B_0015E430;
        shockRequestCalcVol(dldEntry(ref), &buf.v);
        return 0;
    }
    if (DLDTYPE(ref) == _ScriptAnimationObjDef)
        return kickLWS(dldEntry(ref), D_00139F78, D_00139F84, 0, D_00139F88, D_00139F80);
    return 0;
}
#endif
