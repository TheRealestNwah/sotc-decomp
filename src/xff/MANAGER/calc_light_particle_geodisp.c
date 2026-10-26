typedef int Quadword __attribute__((mode(TI)));
typedef union {
    Quadword q;
    float f[4];
} Vector;

typedef struct {
    char pad0[0x10];
    Vector position;
    char pad20[0xA0];
    unsigned long flags;
} ParticleGeo;

extern char *GetGeoDispClass(unsigned char *obj);
extern int func_000C59F0(void *particle);
extern void SetGeoDispClassLightColMan(void *geo);

static inline char **getParticleList(unsigned char *obj)
{
    if (obj)
        return (char **)(GetGeoDispClass(obj) + 0xE8);
    return 0;
}

void calc_light_particle_geodisp(unsigned char *obj)
{
    ParticleGeo *geo = (ParticleGeo *)GetGeoDispClass(obj);
    char *particle = *getParticleList(obj);

    if (func_000C59F0(particle) == 1) {
        geo->position.q = ((Vector *)(particle + 0x20))->q;
        geo->flags &= ~1UL;
        geo->position.f[3] = 1.0f;
        SetGeoDispClassLightColMan(geo);
    }
}
