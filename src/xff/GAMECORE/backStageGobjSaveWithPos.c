/* Saves the stage-object pose into the checkpoint record for its type (0x103 -> B_00183B58, 0x203 -> B_00183B7C; the 0x303 boss slot is not handled here) from an explicit position (-x, y, -z) and rotation triple instead of reading the layout object like backStageGobjSave. Pinning o/pos to $s3/$s2 fixes the saved-register order; listing case 0x303 and storing the id inside each case gives the Original 0x203-first dispatch. */
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


void backStageGobjSaveWithPos(unsigned char *o0, float *pos0, float *rot)
{
    register unsigned char *o __asm__("$19") = o0;
    register float *pos __asm__("$18") = pos0;
    char *s1;
    int t;
    int *cp;

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
        cp = B_00183B58.v;
        *cp++ = *(unsigned short *)(o + 0xE);
        break;
    case 0x203:
        cp = B_00183B7C.v;
        *cp++ = *(unsigned short *)(o + 0xE);
        break;
    case 0x303:
    default:
        return;
    }
    ((float *)cp)[0] = -pos[0];
    ((float *)cp)[1] = pos[1];
    ((float *)cp)[2] = -pos[2];
    ((float *)cp)[3] = rot[0];
    ((float *)cp)[4] = rot[1];
    ((float *)cp)[5] = rot[2];
}
