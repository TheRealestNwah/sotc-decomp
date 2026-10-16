typedef struct {
    const char *name;
    void (*disp)(void);
    int pad;
    void (*clip)(void);
    void (*light)(void);
    int flag;
} GeoDef;

extern char rootPtn[];
extern void disp_particle_geodisp(void);
extern void clip_particle_geodisp(void);
extern void calc_light_particle_geodisp(void);
extern char *CreateGeoDispObj(void *, void *, GeoDef *);

static const char D_0013FD38[] = "particle";
static const GeoDef D_0013FD48 = { D_0013FD38, disp_particle_geodisp, 0, clip_particle_geodisp, calc_light_particle_geodisp, 1 };

char *initParticleObject(void *heap, void *b)
{
    GeoDef def = D_0013FD48;
    char *o = CreateGeoDispObj(heap, b, &def);

    if (o == 0)
        o = CreateGeoDispObj(rootPtn, b, &def);
    *(int *)(o + 0x108) = 0;
    return o;
}
