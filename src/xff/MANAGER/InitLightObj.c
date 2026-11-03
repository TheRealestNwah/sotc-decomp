#ifdef NONMATCHING /* 56 diffs: frame layout and copy loop now match; gcc schedules the field loads/stores differently and keeps &def in s2 for the name store */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct {
    char *name;
    int count;
    char pad08[0x44];
    int kind;
    float range;
    int flags;
    char pad58[0x24];
} LightHeader;
typedef struct {
    LightHeader header;
    int kind;
    Vec4 first;
    Vec4 second;
    float param0;
    float param1;
} LightDefinition;
typedef struct {
    int pad00;
    int kind;
    float first[3];
    float second[4];
    float param0;
} LightSource;
typedef struct {
    char pad00[0x14];
    int kind;
    float range;
    char pad1c[8];
    int flags;
} LightParam;

extern char RO_00119A90[];
extern void *memset(void *, int, unsigned int);
extern unsigned char *CreateLightObj(void *, int, ...);

static inline LightDefinition makeLightDef(LightSource *src, LightParam *param)
{
    LightDefinition def;
    LightDefinition *d = &def;

    memset(&d->header, 0, sizeof(d->header));
    d->header.name = RO_00119A90;
    d->header.count = 1;
    d->header.kind = param->kind;
    d->header.range = param->range;
    d->header.flags = param->flags;
    d->kind = src->kind;
    d->first.f[0] = src->first[0];
    d->first.f[1] = src->first[1];
    d->first.f[2] = src->first[2];
    d->first.f[3] = 0.0f;
    d->second.f[0] = src->second[0];
    d->second.f[1] = src->second[1];
    d->second.f[2] = src->second[2];
    d->param0 = src->second[3];
    d->param1 = src->param0;
    d->second.f[3] = 0.0f;
    return def;
}

void initLightObj(void *heap, LightSource *src, LightParam *param)
{
    CreateLightObj(heap, 0x10, makeLightDef(src, param));
}
#endif
