typedef struct { char *name; int users; int tex; } PT;
extern PT g_ainParticleTextureStore[];
extern int *DldSysUndefSymbol;

typedef struct {
    char *name;
    unsigned int h;
} PtclTexDef;

static inline int *dldData(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (int *)t[4] : 0;
}

static inline int is_same_texture(PT *p, int tex)
{
    if (p->tex == tex && tex != 0)
        return 1;
    return 0;
}

static inline int is_free_texture(PT *p)
{
    if (p->tex == 0)
        return 1;
    return 0;
}

int create_particle_texture_and_get_id(PtclTexDef *def)
{
    int tex = dldData(&def->h)[3];
    int i;

    if (tex != 0) {
        for (i = 0; i < 40; i++) {
            if (is_same_texture(&g_ainParticleTextureStore[i], tex) == 1) {
                PT *q = &g_ainParticleTextureStore[i];
                q->users++;
                return i;
            }
        }
        for (i = 0; i < 40; i++) {
            PT *p = &g_ainParticleTextureStore[i];
            if (is_free_texture(p) == 1) {
                p->name = def->name;
                p->users = 1;
                p->tex = tex;
                return i;
            }
        }
        __asm__ __volatile__("break 0");
    }
    return -1;
}
