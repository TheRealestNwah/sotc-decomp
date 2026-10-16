extern int DldSysUndefSymbol;
extern char gcGlobalVar[];
extern void *SCRGetFirstObj(void *);
extern char *GetAnimationClass(void *);

int SCRConditionHorseMotionCheck(void *a, int b, int c, int d, int e, int f, int g, int i, unsigned int *h)
{
    void *obj = SCRGetFirstObj(gcGlobalVar + 0x2B4);
    char *anim;
    unsigned int v;
    int off;
    char *t;
    char *p;

    if (obj == 0)
        return 0;
    anim = GetAnimationClass(obj);
    v = *h;
    off = v & 0x3FFFF;
    t = off != 0 ? *(char **)((char *)h - off) : 0;
    p = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
    return p == *(char **)anim;
}
