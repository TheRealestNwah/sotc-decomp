#ifdef NONMATCHING /* 1 diff: bnel instead of bne at the _BlendMotionDef check */
extern int DldSysUndefSymbol;
extern int _AnimObjDef;
extern int _BlendMotionDef;

static inline int *dldObj(unsigned int *h)
{
    unsigned int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return (t != 0 && t != (int *)DldSysUndefSymbol) ? t : 0;
}

static inline void *dldElem(unsigned int *h)
{
    unsigned int v = *h;
    unsigned int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    if (t != 0 && t != (int *)DldSysUndefSymbol)
        return (void *)(t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3]);
    return 0;
}
extern unsigned int *getBlendLastMotion(unsigned int *);

char *DebugGetAnimObjName(unsigned int *h)
{
    if ((int *)dldObj(h)[2] == &_AnimObjDef)
        return *(char **)dldElem(h);
    if ((int *)dldObj(h)[2] == &_BlendMotionDef)
        return *(char **)dldElem(getBlendLastMotion(h));
    return 0;
}
#endif
