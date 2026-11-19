/* Parked attempt: 8 words differ from the Original. */
#ifdef NONMATCHING
extern int DldSysUndefSymbol;
extern void *isysGetThisSubThread(void);
extern char *GetCharacterClass(void *);
extern char *GetScriptClass(void *);
extern void AI_SetSurprisedArea(void *, float);

static inline char *dldResolve(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((*h >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

static inline char *dldBase(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) : 0;
}

static void func_000B1FE0(char *a)
{
    void *obj = isysGetThisSubThread();
    char *chr = GetCharacterClass(obj);
    char *scr = GetScriptClass(obj);
    char *d = dldBase(*(unsigned int **)(scr + 0x48));
    float *r;
    float v = *(float *)(*(char **)(chr + 0x1140) + 0x44);

    *(float *)(a + 0x1A8) = 1.0f;
    *(float *)(a + 0x1D0) = v;
    if (d != 0) {
        r = (float *)dldResolve((unsigned int *)d);
        *(float *)(a + 0x18) = *(float *)(d + 4);
        if (r != 0) {
            *(float **)(a + 0x20C) = r;
            *(float *)(a + 0x1A8) = r[0];
            AI_SetSurprisedArea(a + 0x1B4, r[3]);
        }
    }
}
#endif
