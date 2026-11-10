/* ~102 diffs, 5 words short (175 vs 180). Mirror of backStageGobjSave (see that park): resolves the stage object type the same way (dld ref at o+0x10, 0x303 only when the boss test passes), copies the 0x48-byte stage record src into dst (struct copy of unknown alignment: the Original does a runtime 8-byte alignment check and has aligned ld/sd and unaligned ldl/ldr loops), then picks the checkpoint record by type (0x103 -> B_00183B58 when its id != -1, 0x203 -> B_00183B7C likewise, 0x303 -> the boss record B_00183BA0 when its id equals the object id at o+0xE) and, if one is found, copies its 6 floats (position -x,y,-z then euler) into dst+0x18..0x2C and returns 1. The same record layout explains backStageGobjCheckEntry. Remaining diffs: saved-register numbering ($s0/$s1/$s2 are in a different order in the Original) and the struct-copy loop shape. */
extern int *DldSysUndefSymbol;
static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    if (t != 0 && t != DldSysUndefSymbol)
        return (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3];
    return 0;
}

typedef struct {
    int v[0x93];
} CheckPoint;

extern CheckPoint B_00183B58;
extern CheckPoint B_00183B7C;
extern unsigned char B_00183BA0[];
extern void *bossStatGetActiveBoss(void);
extern char *GetLayoutClass(void *);
extern void GetEulerYXZFromQuaternion(float *, void *);


#ifdef NONMATCHING
typedef struct { char b[0x48]; } StageCopy;

int backStageGobjLoad(StageCopy *dst, unsigned char *o, StageCopy *src)
{
    char *s1;
    int t;
    int *rec;
    float *f;

    s1 = dldResolve((unsigned int *)(o + 0x10));
    t = 0;
    if (s1 != 0) {
        t = *(int *)(s1 + 4);
        if (t == 0x303) {
            t = dldResolve((unsigned int *)s1) == bossStatGetActiveBoss() ? *(int *)(s1 + 4) : 0;
        }
    }
    *dst = *src;
    switch (t) {
    case 0x103:
        rec = B_00183B58.v[0] != -1 ? B_00183B58.v : 0;
        break;
    case 0x203:
        rec = B_00183B7C.v[0] != -1 ? B_00183B7C.v : 0;
        break;
    case 0x303:
        rec = *(int *)B_00183BA0 == *(unsigned short *)(o + 0xE) ? (int *)B_00183BA0 : 0;
        break;
    default:
        return 0;
    }
    if (rec != 0) {
        f = (float *)(rec + 1);
        ((float *)dst)[6] = f[0];
        ((float *)dst)[7] = f[1];
        ((float *)dst)[8] = f[2];
        ((float *)dst)[9] = f[3];
        ((float *)dst)[10] = f[4];
        ((float *)dst)[11] = f[5];
        return 1;
    }
    return 0;
}
#endif
