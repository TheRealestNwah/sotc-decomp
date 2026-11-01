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
typedef struct { const char *name; char pad4[0xC4]; } CameraLwsParam;
CameraLwsParam *get_camera_lws_animation_parameter_by_name(unsigned int *resource, const char *name)
{
    if (resource != 0) {
        CameraLwsParam *effect = resourceData(resource);
        int i;
        for (i = 0; i < resourceCount(resource); i++) {
            if (strcmp(effect[i].name, name) == 0)
                return &effect[i];
        }
    }
    return 0;
}
