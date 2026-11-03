extern int *DldSysUndefSymbol;
extern void convert_from_quater_to_rotXYZ_direct_motion_ik_base(float *, void *, int);
extern void convert_from_rotXYZ_to_quater_direct_motion_ik_base(void *, float *, int);

typedef struct {
    float pad0;
    float min;
    float max;
    char pad[0x1C];
} Limit;

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

void func_0003BEB8(void *out, char *ik, void *q)
{
    float rot[4];
    Limit *lim = (Limit *)dldResolve((unsigned int *)(ik + 0xC));
    int i;

    convert_from_quater_to_rotXYZ_direct_motion_ik_base(rot, q, *(int *)(ik + 0x14));
    for (i = 0; i < 3; i++) {
        float a = rot[i] * 57.2957795f;

        rot[i] = a < lim[i].min ? lim[i].min * 0.0174532925f : lim[i].max < a ? lim[i].max * 0.0174532925f : rot[i];
    }
    convert_from_rotXYZ_to_quater_direct_motion_ik_base(out, rot, *(int *)(ik + 0x14));
}
