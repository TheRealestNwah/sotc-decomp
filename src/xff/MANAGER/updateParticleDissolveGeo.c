typedef struct {
    char pad0[0x40];
    float blend_ratio;
} ParticleParameters;
typedef void (*ParticleCreate)(int, int, void *, int, void *);
typedef void (*ParticleToggle)(unsigned char *, int, int);
static void updateParticleGeo(int, void *, int, void *, int, ParticleParameters *, void *,
    unsigned char *, int, int, ParticleCreate, ParticleToggle);
extern int KickParticleGetResourceId(unsigned char *);
extern int set_npe_blend_ratio_particle_emitter(void *, int, float);

static void updateParticleDissolveGeo(int flags, void *geometry, int argument, void *actor,
    int node, ParticleParameters *parameters, void *camera, unsigned char *kick,
    int effect, int mode, ParticleCreate create, ParticleToggle toggle)
{
    updateParticleGeo(flags, geometry, argument, actor, node, parameters, camera,
        kick, effect, mode, create, toggle);
    if (kick != 0)
        set_npe_blend_ratio_particle_emitter((void *)effect,
            KickParticleGetResourceId(kick), parameters->blend_ratio);
}
