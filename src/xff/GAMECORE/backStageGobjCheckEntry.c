/* Companion of backStageGobjSave / backStageGobjLoad: decodes the stage object type from the dld ref at o+0x10 (0x303 only when the boss test passes) and answers whether the checkpoint record for that type is filled: 0x103 -> B_00183B58 id != -1, 0x203 -> B_00183B7C id != -1, 0x303 -> flag set and the boss record id equals the object id at o+0xE. The `((int)p - K) ^ K' != 0` expressions reproduce the Original pointer-minus-constant compare; the empty asm barrier keeps li $v1,-0x24 ahead of the pointer adjustment so the delay slots fill as in the Original. */
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
        {
            int *p = B_00183B7C.v;
            if (*p != -1) {
                int k = -0x24;

                __asm__ volatile("" ::: "memory");
                return (((int)p - 0x24) ^ k) != 0;
            }
        }
        return 0;
    case 0x303:
        if (flag == 0)
            return 0;
        {
            int *p = (int *)B_00183BA0;
            if (*p == *(unsigned short *)(o + 0xE))
                return (((int)p - 0x48) ^ -0x48) != 0;
        }
        return 0;
    default:
        return 0;
    }
}
