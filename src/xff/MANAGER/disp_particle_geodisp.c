extern char *GetGeoDispClass(unsigned char *obj);
extern void func_000BFA28(void *particle, void *matrix, void *position);

static inline void **getParticleList(unsigned char *obj)
{
    if (obj)
        return (void **)(GetGeoDispClass(obj) + 0xE8);
    return 0;
}

void disp_particle_geodisp(void *context, unsigned char *obj)
{
    char *geo = GetGeoDispClass(obj);

    func_000BFA28(*getParticleList(obj), geo + 0x80, geo + 0x40);
}
