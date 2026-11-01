typedef union {
    struct {
        char *name;
        int users;
        int tex;
    } s;
} PT;

extern PT g_ainParticleTextureStore[];
extern char g_sPtclNullName[];
extern void iosFree(void *);

typedef struct {
    char pad0[8];
    unsigned int tex;
    char padC[0x1BC - 0xC];
} LodItem;

typedef struct {
    char pad0[0xD0];
    int count;
    LodItem *items;
} Lod;

static inline int has_tex(PT *p)
{
    return p->s.tex != 0;
}

static inline int is_proper_particle_texture_id(unsigned int i)
{
    if (i < 40 && has_tex(&g_ainParticleTextureStore[i]))
        return 1;
    return 0;
}

static inline void quit_particle_texture_user_by_id(unsigned int i)
{
    PT *texture;

    if (is_proper_particle_texture_id(i) == 1) {
        texture = &g_ainParticleTextureStore[i];
        if (--texture->s.users <= 0) {
            texture->s.name = g_sPtclNullName;
            texture->s.users = 0;
            texture->s.tex = 0;
        }
    }
}

void check_free_particle_effect_lod(Lod *lod)
{
    int i;

    if (lod == 0)
        return;
    for (i = 0; i < lod->count; i++)
        quit_particle_texture_user_by_id(lod->items[i].tex);
    {
        LodItem **pp = &lod->items;

        if (*pp) {
            iosFree(*pp);
            *pp = 0;
        }
    }
    iosFree(lod);
}
