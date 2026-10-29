extern int *DldSysUndefSymbol;
extern int strcmp(const char *, const char *);
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
typedef struct { char pad0[0x14]; const char *name; } WindEffect;
WindEffect *get_wind_effect_data(unsigned int *resource, const char *name)
{
    if (resource != 0) {
        int count = resourceCount(resource);
        WindEffect *effects = resourceData(resource);
        int i;
        for (i = 0; i < count; i++) {
            if (strcmp(effects[i].name, name) == 0)
                return &effects[i];
        }
    }
    return 0;
}
