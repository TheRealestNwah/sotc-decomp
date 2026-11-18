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

static inline void check_free_particle_effect_lod(Lod *lod)
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

extern Lod *create_particle_effect_lod(void);
extern int set_npe_file_data_to_particle_effect_lod(Lod *, void *, void *);
extern int set_except_npe_file_data_to_particle_effect_lod(Lod *, void *, void *, void *);
extern void init_particle_effect_lod(Lod *);

static Lod *create_and_init_particle_effect_lod(void *a, void *b, void *c, void *d, void *e)
{
    Lod *lod;
    int ok;
    int r;

    ok = 0;
    lod = create_particle_effect_lod();
    if (lod != 0) {
        r = set_npe_file_data_to_particle_effect_lod(lod, a, b);
        if (r == 1 && set_except_npe_file_data_to_particle_effect_lod(lod, c, d, e) == r) {
            init_particle_effect_lod(lod);
            ok = 1;
        }
    }
    if (!ok) {
        check_free_particle_effect_lod(lod);
        lod = 0;
    }
    return lod;
}
