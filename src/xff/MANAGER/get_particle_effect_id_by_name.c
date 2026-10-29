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
typedef struct { char pad0[0x24]; const char *name; char pad28[0x2C]; } ParticleEffect;
ParticleEffect *get_particle_effect_id_by_name(unsigned int *resource, const char *name)
{
    if (resource != 0) {
        ParticleEffect *effect = resourceData(resource);
        int i;
        for (i = 0; i < resourceCount(resource); i++) {
            if (strcmp(effect[i].name, name) == 0)
                return &effect[i];
        }
    }
    return 0;
}
