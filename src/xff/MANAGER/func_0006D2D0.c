#ifdef NONMATCHING
/* 108 diffs, same length (123 words). Draft from the asm (MANAGER); callee prototypes are guesses. Finds a local-Y geometry point for the root dynamics, parents the layout object to it, reads the limit mode (with the force-no-limit / no-limit overrides picked from the flag word behind root+0x1C0+0xC, plus an optional callback at root+0xC30), then computes the fitted quaternion and the parent offset. Frame (0xB0) and the call structure match; the callee-saved assignment does not: the Original holds root+0xC0 in $s3, root+0xE20 in $s4, root[0x134] in $s5, root+0x6D0 in $s6 and root[0x13C] in $s2, and loads root[0x40C] right after ParentLayoutObj. Declaration-order permutations did not change it. */
extern int *DldSysUndefSymbol;

static inline char *dldBase(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? (char *)t[4] : 0;
}

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    if (t != 0 && t != DldSysUndefSymbol)
        return (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3];
    return 0;
}

extern int charrootdyn_findLocalYGeometryPoint(void *, void *, void *, void *, float);
extern void ParentLayoutObj(void *, void *);
extern void charrootdyn_getLimitMode(void *, void *);
extern void charrootdyn_getForceNoLimitMode(void *, void *);
extern void charrootdyn_getNoLimitMode(void *, void *);
extern void charrootdyn_getCompleteFittingYQFromStabGPWithSlopeLimit(void *, void *, void *, void *, void *, float, float);
extern void SetLayoutClassRootQuaternion(void *, void *);
extern void charrootdyn_getLocalYGlobalXZOffsetFromParentGP(void *, void *, void *, void *, void *);

void func_0006D2D0(void *obj, char *root)
{
    char gp[0x50];
    char mode[0x10];
    char *s3 = root + 0xC0;
    char *s4 = root + 0xE20;
    char *s6 = root + 0x6D0;
    char *s5 = *(char **)(root + 0x134);
    char *s2 = *(char **)(root + 0x13C);
    unsigned int *flags;
    float lim;

    if (charrootdyn_findLocalYGeometryPoint(gp, s2, s5, s4, *(float *)(root + 0xE34)) == 0)
        return;
    ParentLayoutObj(obj, gp);
    lim = *(float *)(root + 0x40C);
    flags = (unsigned int *)dldResolve((unsigned int *)(*(char **)(root + 0x1C0) + 0xC));
    charrootdyn_getLimitMode(mode, root);
    if (flags != 0) {
        if (*flags & 1)
            charrootdyn_getForceNoLimitMode(mode, root);
        if ((*flags >> 1) & 1)
            charrootdyn_getNoLimitMode(mode, root);
        if ((*flags >> 2) & 1) {
            int (*cb)(void *, void *, void *, void *) = *(int (**)(void *, void *, void *, void *))(root + 0xC30);

            if (cb != 0 && *(int *)(root + 0x124) != 0) {
                if (cb(s3, root, s4, s2) == 0)
                    charrootdyn_getForceNoLimitMode(mode, root);
            }
        }
    }
    charrootdyn_getCompleteFittingYQFromStabGPWithSlopeLimit(s2, s3, s4, s2, mode, lim, lim);
    SetLayoutClassRootQuaternion(root, s2);
    charrootdyn_getLocalYGlobalXZOffsetFromParentGP(s6, root + 0x6E0, s2, s5, s3);
}
#endif
