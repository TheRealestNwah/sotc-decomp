extern int DldSysUndefSymbol;
extern char *MotRootDyn_NOROOTDYNAMICS_VEL_XZSTAB;
extern char *MotRootDyn_NOROOTDYNAMICS_VEL;
extern char *MotRootDyn_NOROOTDYNAMICS_POS_FREE;
extern void GetMotionRootInfo(void *, void *, void *, float, float, float);
extern void GetMotionRootShiftInfo(void *, void *, void *, void *, float, float, float, float, float, void *);

int charrootdyn_getMotionRootInfo(void *a, void *b, char *c, void *d, float f)
{
    char *s = c + 0x1C0;

    if (c[0x360] != 0) {
        char *m = *(char **)(s + 4);
        char *res = m + 0x50;
        unsigned int *h;
        unsigned int v;
        int off;
        char *t;
        char *dyn;

        if (res == 0)
            return 0;
        h = (unsigned int *)(m + 8);
        v = *h;
        off = v & 0x3FFFF;
        t = off != 0 ? *(char **)((char *)h - off) : 0;
        dyn = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
        if (dyn != MotRootDyn_NOROOTDYNAMICS_VEL_XZSTAB && dyn != MotRootDyn_NOROOTDYNAMICS_VEL && dyn != MotRootDyn_NOROOTDYNAMICS_POS_FREE) {
            GetMotionRootShiftInfo(a, b, d, res, *(float *)(s + 8), *(float *)(s + 0xC), *(float *)(s + 0x10), *(float *)(s + 0x14), f, c + 0x5A0);
            return 1;
        }
    }
    GetMotionRootInfo(a, b, d, *(float *)(s + 8), *(float *)(s + 0xC), f);
    return 1;
}
