/* Kicks the sound, LWS animation, shock or particle that a kick definition targets, if its condition (underwater check) passes. */
#ifdef NONMATCHING
/* Parked: 21 diffs, same size (282 words). Remaining: the condition flag lands in a1 instead of v1 (bne instead of bnel at 0xFC),
   the charrootdyn_checkUnderWater argument setup order, and the 0/1 conversion of its result (sltu + 64-bit zero-extend instead of bnez/li 1/li 0). */
typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec;
typedef struct {
    char pad0[4];
    unsigned int target;
    char pad8[0x28 - 8];
    unsigned int cond;
} KickDef;
extern int *DldSysUndefSymbol;
extern int *GPConditionCheckType_UNDERWATER;
extern int D_00139F78;
extern int D_00139F84;
extern int D_00139F88;
extern char _SeList[], _ScriptAnimationObjDef[], _ShockList[];
extern void func_000EC988(void *, KickDef *);
extern void GetGeometryPointerPosition(Vec *, void *);
extern char *GetCharacterClass(int);
extern int charrootdyn_checkUnderWater(Vec *, Vec *, int *, void *, float);
extern int SequenceKickSE(char *, void *);
extern int kickLWS(char *, int, int, int, int, void *);
extern void shockRequestCalcVol(char *, Vec *);
extern int SequenceKickParticle(char *, void *);

static inline char *resolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static inline int *resolveSym(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? t : 0;
}

static inline int underWater(char *geo)
{
    Vec pos;
    Vec out;
    int *p;
    char *c;
    char *c2;

    GetGeometryPointerPosition(&pos, geo);
    c = GetCharacterClass(D_00139F78);
    c2 = GetCharacterClass(D_00139F78);
    p = *(int **)(c + 0xE38) + *(short *)(c2 + 0x370);
    return charrootdyn_checkUnderWater(&out, &pos, p, GetCharacterClass(D_00139F78) + 0xE20, 0.0f);
}

int func_000ECCF8(KickDef *def)
{
    char geo[0x40];
    char *cond;
    unsigned long ok;

    if (resolve(&def->target) != 0) {
        func_000EC988(geo, def);
        cond = resolve(&def->cond);
        ok = 1;
        if (cond != 0) {
            if ((int *)cond != GPConditionCheckType_UNDERWATER) {
                ok = 0;
            } else if (underWater(geo)) {
                ok = 1;
            } else {
                ok = 0;
            }
        }
        if (ok) {
            if (resolveSym(&def->target)[2] == (int)_SeList) {
                return SequenceKickSE(resolve(&def->target), geo);
            }
            if (resolveSym(&def->target)[2] == (int)_ScriptAnimationObjDef) {
                return kickLWS(resolve(&def->target), D_00139F78, D_00139F84, 0, D_00139F88, geo);
            }
            if (resolveSym(&def->target)[2] == (int)_ShockList) {
                Vec pos2;

                GetGeometryPointerPosition(&pos2, geo);
                shockRequestCalcVol(resolve(&def->target), &pos2);
                return 0;
            }
            return SequenceKickParticle(resolve(&def->target), geo);
        }
        return 0;
    }
    return 0;
}
#else
extern int func_000ECCF8(void *def);
#endif
