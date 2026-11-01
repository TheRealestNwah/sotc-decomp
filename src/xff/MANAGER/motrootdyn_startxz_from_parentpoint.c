typedef int s128 __attribute__((mode(TI)));
extern s128 YUnitVector;
extern s128 ZeroVector;
extern void charrootdyn_parentpointxzfitstab(char *, int, int);
extern void charrootdyn_getCompleteFittingYQFromYDir(void *, void *, void *);
extern void SetLayoutClassRootQuaternion(char *, void *);
extern int charrootdyn_getLandingSurface(void *, void *, void *, void *, float);
extern int ParentLayoutObj(void *, void *);
extern void ForceUnparentLayoutObj(void *);
extern void charrootdyn_getLocalOffsetFromParentGP(char *, void *, void *, char *);

void motrootdyn_startxz_from_parentpoint(void *actor, char *c, float *e)
{
    char buf[0x50];
    void *q;

    charrootdyn_parentpointxzfitstab(c, *(int *)(c + 0x1C4), 0);
    q = *(void **)(c + 0x13C);
    charrootdyn_getCompleteFittingYQFromYDir(q, &YUnitVector, q);
    SetLayoutClassRootQuaternion(c, *(void **)(c + 0x13C));
    if (charrootdyn_getLandingSurface(buf, c + 0xE20, *(void **)(c + 0x134), *(void **)(c + 0x134),
                                      -e[1] - *(float *)(c + 0x3D8))) {
        ParentLayoutObj(actor, buf);
        charrootdyn_getLocalOffsetFromParentGP(c + 0x6D0, *(void **)(c + 0x13C), *(void **)(c + 0x134), c + 0xC0);
    } else {
        ForceUnparentLayoutObj(actor);
    }
    *(s128 *)(c + 0xAB0) = ZeroVector;
    *(int *)(c + 0xB54) = 0;
}
