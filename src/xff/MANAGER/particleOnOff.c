extern int KickParticleGetResourceId(char *);
extern int set_generate_particle_flag(int, int, int);

int particleOnOff(char *name, int a, int b)
{
    if (name == 0)
        return 0;
    return set_generate_particle_flag(a, KickParticleGetResourceId(name), b);
}
