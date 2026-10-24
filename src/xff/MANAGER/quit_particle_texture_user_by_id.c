typedef struct { char *name; int users; int tex; } PT;
extern PT g_ainParticleTextureStore[];
extern char g_sPtclNullName[];

static inline int is_proper_particle_texture_id(unsigned int i)
{
    if (i < 40 && g_ainParticleTextureStore[i].tex != 0)
        return 1;
    return 0;
}

void quit_particle_texture_user_by_id(unsigned int i)
{
    PT *texture;

    if (is_proper_particle_texture_id(i) == 1) {
        texture = &g_ainParticleTextureStore[i];
        if (--texture->users <= 0) {
            texture->tex = 0;
            texture->users = 0;
            texture->name = g_sPtclNullName;
        }
    }
}
