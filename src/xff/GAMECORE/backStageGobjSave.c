/* Saves the stage-object pose into one of three checkpoint records picked by the object type (0x103 -> B_00183B58, 0x203 -> B_00183B7C, 0x303 -> B_00183BA0 boss slot, only when the boss test passes), storing the object id, then the position (-x, y, -z) and the Euler angles in degrees (x, -y, z). The store sequence is a static inline called once per case, so gcc crossjumps the three identical tails. The empty asm on cp keeps the record address a register; the PU union load (alias set 0) makes the position pointer reload after every float store. The scaled angles are computed after the position stores in the order x, z, y, which gives the Original multiply order. */
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

typedef union {
    float *p;
    int i;
} PU;

static inline void saveCp(float *cp, unsigned char *o, float *eul)
{
    char *lc;
    float e0, e1, e2, m0, m1, m2;
    __asm__("" : "+r"(cp));
    *(int *)cp++ = *(unsigned short *)(o + 0xE);
    lc = GetLayoutClass(*(void **)(o + 8));
    GetEulerYXZFromQuaternion(eul, *(void **)(lc + 0x13C));
    e1 = eul[1]; e0 = eul[0]; e2 = eul[2];
    cp[0] = -((PU *)(lc + 0x134))->p[0];
    cp[1] = ((PU *)(lc + 0x134))->p[1];
    cp[2] = -((PU *)(lc + 0x134))->p[2];
    m0 = e0 * 57.29578f; m2 = e2 * 57.29578f; m1 = -(e1 * 57.29578f);
    cp[3] = m0; cp[4] = m1; cp[5] = m2;
}
void backStageGobjSave(unsigned char *o)
{
    float eul[4];
    char *s1;
    int t;

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
    switch (t) {
    case 0x103:
        saveCp((float *)B_00183B58.v, o, eul);
        break;
    case 0x203:
        saveCp((float *)B_00183B7C.v, o, eul);
        break;
    case 0x303:
        saveCp((float *)B_00183BA0, o, eul);
        break;
    }
}

