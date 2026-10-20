typedef struct {
    int name;
    int disp;
    int pad;
    int clip;
    int light;
    int flag;
} GeoDef;

extern char rootPtn[];
extern void disp_particle_geodisp(void);
extern void clip_particle_geodisp(void);
extern void calc_light_particle_geodisp(void);
extern char *CreateGeoDispObj(void *, int, GeoDef *);

static const char D_0013FD38[] = "particle";
static const GeoDef D_0013FD48 = { (int)D_0013FD38, (int)disp_particle_geodisp, 0, (int)clip_particle_geodisp, (int)calc_light_particle_geodisp, 1 };

char *initParticleObject(void *heap, int b)
{
    GeoDef def = D_0013FD48;
    char *o = CreateGeoDispObj(heap, b, &def);

    if (o == 0)
        o = CreateGeoDispObj(rootPtn, b, &def);
    *(int *)(o + 0x108) = 0;
    return o;
}
