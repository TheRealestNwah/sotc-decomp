typedef int Quadword __attribute__((mode(TI)));
typedef union {
    Quadword q;
    float f[4];
} Vector;

typedef struct {
    char pad0[0x20];
    Vector projected;
    float clipState;
} ParticleGeo;

extern char *GetGeoDispClass(unsigned char *obj);
extern int func_000C5980(void *particle);
extern void *iosgluGetCameraContext(void);
extern void getZ(void *out, void *sphere, void *matrix);

static inline char **getParticleList(unsigned char *obj)
{
    if (obj)
        return (char **)(GetGeoDispClass(obj) + 0xE8);
    return 0;
}

void clip_particle_geodisp(unsigned char *obj)
{
    char *particle = *getParticleList(obj);
    ParticleGeo *geo = (ParticleGeo *)GetGeoDispClass(obj);

    if (func_000C5980(particle) == 1) {
        Vector sphere;
        Vector projected;

        sphere.q = ((Vector *)(particle + 0x20))->q;
        sphere.f[3] = 0.0f;
        geo->clipState = 0.0f;
        getZ(&projected, &sphere, (char *)iosgluGetCameraContext() + 0x1A0);
        geo->projected.f[2] = projected.f[2];
        geo->projected.f[1] = projected.f[1];
        geo->projected.f[0] = projected.f[0];
        if (geo->projected.f[0] <= 0.0f)
            geo->projected.f[0] = 0.01f;
    } else {
        geo->clipState = -1.0f;
    }
}
