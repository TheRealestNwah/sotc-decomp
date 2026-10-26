extern int KickParticleGetResourceId(unsigned char *object);
extern int set_generate_particle_flag(int, int, int);

int particleOnOff(unsigned char *object, int a, int b)
{
    if (object == 0)
        return 0;
    return set_generate_particle_flag(a, KickParticleGetResourceId(object), b);
}
