typedef struct { int a, b, tex; } PT;
extern PT g_ainParticleTextureStore[];
extern void texTransRequest(int, int, int);
void set_particle_texture_by_id(int i)
{
    texTransRequest(g_ainParticleTextureStore[i].tex, 0, 0);
}
