#ifdef NONMATCHING
/* 9 diffs, same size (131 words). Saves the stage-object pose into one of three checkpoint records picked by the object type (0x103 -> B_00183B58, 0x203 -> B_00183B7C, 0x303 -> B_00183BA0 boss slot, only when the boss test passes), storing the object id, then the position (-x, y, -z) and the Euler angles in degrees (x, -y, z). The type is read from the dld ref at o+0x10 (same decoding as the sibling backStageGobjCheckEntry). The store sequence is a static inline called once per case: gcc crossjumps the three identical tails, which gives the Original's per-case lhu in the beql delay slots, and the per-case constant record address lets alias analysis keep the eul loads ahead of the record stores. The PU union load (alias set 0) makes the position pointer reload after every float store, as in the Original. Remaining diff (all in the merged tail): the Original increments the record pointer in place (sw id,0($s0); addiu $s0,$s0,4) and stores the six floats at 0x0..0x14 off it; ours keeps the base in $s0, puts base+4 in $s2 for the first float only, stores the rest at 0x8..0x18 off the base, and hoists lw $a0,8($s2) above the id store. Index stores after cp++ give the right offsets but move the base into $v0 (28 diffs); a single non-inline cp after the switch increments in place but loses the alias info and the crossjumped dispatch (64). */
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
    *(int *)cp++ = *(unsigned short *)(o + 0xE);
    lc = GetLayoutClass(*(void **)(o + 8));
    GetEulerYXZFromQuaternion(eul, *(void **)(lc + 0x13C));
    *cp++ = -((PU *)(lc + 0x134))->p[0];
    *cp++ = ((PU *)(lc + 0x134))->p[1];
    *cp++ = -((PU *)(lc + 0x134))->p[2];
    *cp++ = eul[0] * 57.29578f;
    *cp++ = -(eul[1] * 57.29578f);
    *cp++ = eul[2] * 57.29578f;
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
#endif
