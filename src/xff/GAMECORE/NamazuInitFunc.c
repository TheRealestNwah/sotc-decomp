typedef struct {
    char pad[0x24];
    float radius;
    float scale;
    char pad2C[0x8];
} AnimalType;

typedef struct {
    char pad[0x10];
    AnimalType *types;
} AnimalTypeTable;

typedef struct {
    char pad[0x10];
    float minRadius;
    short type;
    char pad16[0x8];
    unsigned short flags;
    float maxRadius;
} SpawnParam;

extern AnimalTypeTable SH_SmallAnimalTypeDEFAULT;
extern void AI_GetRandomCylinderOfs(float *, float, float, float, float);

static inline void vecAddXYZ(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

int NamazuInitFunc(float *pos, void *a1, void *a2, SpawnParam *p, int force)
{
    AnimalType *types = SH_SmallAnimalTypeDEFAULT.types;
    float ofs[4];
    float rmin, rmax, s;
    int ret = 0;

    if (p == 0)
        return ret;
    if (types == 0)
        return ret;
    if ((p->flags & 1) && !force) {
        rmax = 0.0f;
        rmin = rmax;
    } else {
        float r = types[p->type].radius;
        float a = p->minRadius;
        float b = p->maxRadius * 0.6f;

        rmin = r < a ? r : a;
        rmax = r < b ? r : b;
    }
    s = types[p->type].scale;
    AI_GetRandomCylinderOfs(ofs, rmin * s, rmin, rmax * s, rmax);
    vecAddXYZ(pos, pos, ofs);
    return ret;
}
