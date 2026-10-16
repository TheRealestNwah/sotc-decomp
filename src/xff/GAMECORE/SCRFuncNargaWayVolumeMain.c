extern int DldSysUndefSymbol;
extern char *GetSCRCharaAIWorkPtr(void *);
extern char *GetLayoutClass(void *);
extern void CheckCollisionInsideOfSurfaceXZ(void *, void *, void *);

void SCRFuncNargaWayVolumeMain(void *a, int b, int c, int d, int e, int *h)
{
    char *ai = GetSCRCharaAIWorkPtr(a);
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    int *o = (t != 0 && t != (int *)DldSysUndefSymbol) ? (int *)t[4] : 0;
    void *g;

    if (o != 0 && (g = (void *)o[2]) != 0)
        CheckCollisionInsideOfSurfaceXZ(ai + 0x5AA8, g, *(void **)(GetLayoutClass(a) + 0x134));
}
