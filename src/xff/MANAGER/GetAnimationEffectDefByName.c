extern int *DldSysUndefSymbol;
extern int strcmp(const char *, const char *);
typedef struct { int flags; const char *name; } AnimationEffect;
static inline int resourceCount(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? t[3] : 0;
}
static inline void *resourceData(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? (void *)t[4] : 0;
}
AnimationEffect *GetAnimationEffectDefByName(unsigned int *resource, const char *name)
{
    int count = resourceCount(resource);
    if (count != 0) {
        AnimationEffect *effect = resourceData(resource);
        for (; count != 0; count--, effect++) {
            if (strcmp(effect->name, name) == 0)
                return effect;
        }
    }
    return 0;
}
