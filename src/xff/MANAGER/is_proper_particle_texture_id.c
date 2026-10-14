typedef struct { int a, b, tex; } PT;
extern PT g_ainParticleTextureStore[];
int is_proper_particle_texture_id(unsigned int i)
{
    if (i < 40 && g_ainParticleTextureStore[i].tex != 0)
        return 1;
    return 0;
}
