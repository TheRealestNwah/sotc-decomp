extern void *DldSysUndefSymbol;
extern float ZUnitVector[];
extern void GetQuaternionFromDir(void *out, void *from, void *to, int flag);
extern void SetGeometryPointerGlobalState(void *geom, void *quat, void *pos);
extern int get_particle_effect_id_from_sheet(void *sheet);
extern int boot_particle_emitter_extend(int effect, void *geom, int a, int b, int c);

static inline void *resourceData(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

typedef struct {
    float v[4];
} Quat;

typedef struct {
    float m[16];
} Geom;

#ifdef NONMATCHING
/* 1 diffs: &l.g kept in a saved register instead of recomputed before each call */
static void func_000C2520(void *pos, void *dir, char *def)
{
    struct { Quat q; Geom g; } l;

    if (def != 0) {
        GetQuaternionFromDir(&l.q, ZUnitVector, dir, 1);
        SetGeometryPointerGlobalState(&l.g, &l.q, pos);
        boot_particle_emitter_extend(get_particle_effect_id_from_sheet(resourceData((unsigned int *)(def + 0x38))), &l.g, 0, 0, 0);
        boot_particle_emitter_extend(get_particle_effect_id_from_sheet(resourceData((unsigned int *)(def + 0x3C))), &l.g, 0, 0, 0);
        boot_particle_emitter_extend(get_particle_effect_id_from_sheet(resourceData((unsigned int *)(def + 0x40))), &l.g, 0, 0, 0);
    }
}
#endif
