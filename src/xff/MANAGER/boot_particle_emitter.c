extern int boot_particle_emitter_extend(int, int, int, int, int);

int boot_particle_emitter(int a, int b, int c, int d)
{
    return boot_particle_emitter_extend(a, b, c, d, 0);
}
