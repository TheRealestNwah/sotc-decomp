#ifdef NONMATCHING
/* 53 diffs, 3 words short (128 vs 131). Draft from the asm: saves the stage-object pose into one of three checkpoint records picked by the object type (0x103 -> B_00183B58, 0x203 -> B_00183B7C, 0x303 -> B_00183BA0 boss slot, only when the boss test passes), storing the object id, then the position (-x, y, -z) and the Euler angles in degrees (x, -y, z). The type is read from the dld ref at o+0x10 (same decoding as the sibling backStageGobjCheckEntry). Difference: the Original loads the id (lhu 0xE) in the delay slot of each case branch and keeps the checkpoint pointer in $s0 with the layout class in $s1 (3 more words of case dispatch); ours loads it once after the switch and swaps $s0/$s1. Case order and per-case id loads did not change it. */
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

void backStageGobjSave(unsigned char *o)
{
    float eul[4];
    char *s1;
    int t;
    int *cp;
    char *lc;
    float *pos;
    int id;

    if (o == 0)
        return;
    s1 = dldResolve((unsigned int *)(o + 0x10));
    t = 0;
    if (s1 != 0) {
        t = *(int *)(s1 + 4);
        if (t == 0x303) {
            t = dldResolve((unsigned int *)s1) == bossStatGetActiveBoss() ? *(int *)(s1 + 4) : 0;
        }
    }
    id = *(unsigned short *)(o + 0xE);
    switch (t) {
    case 0x103:
        cp = B_00183B58.v;
        break;
    case 0x203:
        cp = B_00183B7C.v;
        break;
    case 0x303:
        cp = (int *)B_00183BA0;
        break;
    default:
        return;
    }
    *cp = id;
    cp++;
    lc = GetLayoutClass(*(void **)(o + 8));
    GetEulerYXZFromQuaternion(eul, *(void **)(lc + 0x13C));
    pos = *(float **)(lc + 0x134);
    ((float *)cp)[0] = -pos[0];
    ((float *)cp)[1] = pos[1];
    ((float *)cp)[2] = -pos[2];
    ((float *)cp)[3] = eul[0] * 57.29578f;
    ((float *)cp)[4] = -(eul[1] * 57.29578f);
    ((float *)cp)[5] = eul[2] * 57.29578f;
}
#endif
