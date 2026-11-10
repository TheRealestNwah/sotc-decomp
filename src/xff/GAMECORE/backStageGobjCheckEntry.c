/* ~47 diffs, 1 word short (115 vs 116). Companion of backStageGobjSave / backStageGobjLoad: decodes the stage object type from the dld ref at o+0x10 (0x303 only when the boss test passes) and answers whether the checkpoint record for that type is filled: 0x103 -> B_00183B58 id != -1, 0x203 -> B_00183B7C id != -1, 0x303 -> flag set and the boss record id equals the object id at o+0xE. The `((int)cp - K) ^ -K) != 0` expressions reproduce the Original pointer-minus-constant compare it emits for the last two cases. The remaining diffs are the case dispatch order / the address register ($v0 vs $a1) in each case. */
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
int backStageGobjCheckEntry(unsigned char *o, int flag)
{
    char *s1;
    int t;

    s1 = dldResolve((unsigned int *)(o + 0x10));
    t = 0;
    if (s1 != 0) {
        t = *(int *)(s1 + 4);
        if (t == 0x303) {
            t = dldResolve((unsigned int *)s1) == bossStatGetActiveBoss() ? *(int *)(s1 + 4) : 0;
        }
    }
    switch (t) {
    case 0x103:
        return B_00183B58.v[0] != -1;
    case 0x203:
        if (B_00183B7C.v[0] == -1)
            return 0;
        return (((int)&B_00183B7C - 0x24) ^ -0x24) != 0;
    case 0x303:
        if (flag == 0)
            return 0;
        if (*(int *)B_00183BA0 != *(unsigned short *)(o + 0xE))
            return 0;
        return (((int)B_00183BA0 - 0x48) ^ -0x48) != 0;
    default:
        return 0;
    }
}
#endif
