typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
typedef struct Ptn Ptn;
extern Ptn rootPtn;
extern char *GetLayoutClass(void *);
extern char B_0018A970[];
extern void GetGeometryPointerPosition(Vec4 *, void *);
extern int T_0004D8B0(char *, int, Vec4 *, int, int);
extern char *bossStatGetActiveBoss(void);
extern void fsEffectCreateSetScriptSheetSeg(Ptn *, void *, char *);

void effect_death(void *o)
{
    Vec4 pos;
    char *m;
    char *l = GetLayoutClass(o);
    GetGeometryPointerPosition(&pos, B_0018A970);
    m = *(char **)(l + 0x144);
    if (T_0004D8B0(l, *(int *)(*(char **)m + 0x20), &pos, *(int *)(*(char **)(m + 0xC) + 0x104), *(short *)(l + 0x1B4))) {
        fsEffectCreateSetScriptSheetSeg(&rootPtn, o, bossStatGetActiveBoss() + 0x40);
        o = 0;
    }
}
