/* ~125 diffs, same length (194 words). Per-frame fallen-leaf effect update: resolves the layout object (dld handle) for the leaf area, builds a padded min/max box around obj+0x20 (half extents 0x20/0x24 or explicit 0x34/0x38 when a2[0x30] is set, plus p+0x10 and d+0x14 margins), clips it against the camera frustum (clipByMinMaxCube vs camera ctx+0x5A0) and, when visible, runs func_00053058, copies 6 init floats into the work, runs func_00052A38 per leaf (stride 0x80), func_00052D18 per group (stride 0x40), then func_00053AE0 and func_00053650. Same structure as the original; the remaining diffs are s2/s3 register assignment (original: s2 = work[0], s3 = init data) and the scheduling of the box math (original loads the quad into min (0x10) and max (0x0) with sq before the lw 0x30($a2), and interleaves lwc1s differently). */
typedef int s128 __attribute__((mode(TI)));
extern int DldSysUndefSymbol;
extern int *getSpecialEffectObjWork(void *);
extern char *getEditWorkInitData(int);
extern char *iosgluGetCameraContext(void);
extern int clipByMinMaxCube(void *, void *, void *);
extern void func_00053058(void *, void *, void *);
extern void func_00052A38(void *);
extern void func_00052D18(void *, void *);
extern void func_00053AE0(void *, void *, void *, void *, void *);
extern void func_00053650(void *, void *, void *, void *);

#ifdef NONMATCHING
void fallenLeafMain(char *obj)
{
    int *w = getSpecialEffectObjWork(obj);
    char *s7 = (char *)w[2];
    char *s6 = (char *)w[1];
    char *s4 = s7;
    int *s2 = (int *)w[0];
    char *d = getEditWorkInitData(*(int *)(*(char **)(obj + 0x1C) + 8));
    char *a2 = *(char **)(obj + 0x1C);
    char *s0 = s6;
    unsigned int *h = (unsigned int *)(a2 + 0x1C);
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    char *p = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
    struct { s128 a; } hi, lo;
    float *mn = (float *)&hi;
    float *mx = (float *)&lo;
    int i;
    int clipped;

    lo.a = *(s128 *)(obj + 0x20);
    hi.a = lo.a;
    if (*(int *)(a2 + 0x30) != 0) {
        mn[0] = mn[0] - (*(float *)(a2 + 0x34) + *(float *)(p + 0x10) + *(float *)(d + 0x14));
        mn[2] = mn[2] - (*(float *)(a2 + 0x34) + *(float *)(p + 0x10) + *(float *)(d + 0x14));
        mx[0] = mx[0] + (*(float *)(a2 + 0x38) + *(float *)(p + 0x10) + *(float *)(d + 0x14));
        mx[2] = mx[2] + (*(float *)(a2 + 0x38) + *(float *)(p + 0x10) + *(float *)(d + 0x14));
    } else {
        mn[0] = mn[0] - (*(float *)(a2 + 0x20) * 0.5f + *(float *)(p + 0x10) + *(float *)(d + 0x14));
        mn[2] = mn[2] - (*(float *)(a2 + 0x24) * 0.5f + *(float *)(p + 0x10) + *(float *)(d + 0x14));
        mx[0] = mx[0] + (*(float *)(a2 + 0x20) * 0.5f + *(float *)(p + 0x10) + *(float *)(d + 0x14));
        mx[2] = mx[2] + (*(float *)(a2 + 0x24) * 0.5f + *(float *)(p + 0x10) + *(float *)(d + 0x14));
    }
    clipped = clipByMinMaxCube(mn, mx, iosgluGetCameraContext() + 0x5A0);
    s2[0x118 / 4] = 0;
    s2[0x11C / 4] = 0;
    if (clipped == 0) {
        func_00053058(obj, s2, s6);
        *(float *)((char *)s2 + 0xFC) = *(float *)(d + 0x10);
        *(float *)((char *)s2 + 0x100) = *(float *)(d + 0x14);
        *(float *)((char *)s2 + 0x104) = *(float *)(d + 0x18);
        *(float *)((char *)s2 + 0x108) = *(float *)(d + 0x1C);
        *(float *)((char *)s2 + 0x10C) = *(float *)(d + 0x20);
        *(float *)((char *)s2 + 0x110) = *(float *)(d + 0x24);
        for (i = 0; i < s2[0xF4 / 4]; i++, s0 += 0x80)
            func_00052A38(s0);
        for (i = 0; i < s2[0x120 / 4]; i++, s4 += 0x40)
            func_00052D18(s2 + 0x120 / 4, s4);
        func_00053AE0(obj, s2, s6, d, s7);
        func_00053650(obj, s2, s6, d);
    }
}
#endif
