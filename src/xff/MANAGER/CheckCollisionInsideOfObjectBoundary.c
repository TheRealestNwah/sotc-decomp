typedef struct {
    char pad0[0x2C];
    float radius;
} BoundaryData;

typedef struct {
    char pad0[0x20];
    BoundaryData *data;
} CollisionInfo;

typedef struct {
    char pad0[0x90];
    float scale;
    char pad94[0x134 - 0x94];
    float *center;
    char pad138[0x184 - 0x138];
    CollisionInfo *collision;
    char pad188[0x1B8 - 0x188];
    char active;
    char pad1B9[2];
    char boundaryEnabled;
} LayoutClass;

extern LayoutClass *GetLayoutClass(void *);

static inline float squareDistance(float *a, float *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

int CheckCollisionInsideOfObjectBoundary(void *object, float *position, float margin)
{
    LayoutClass *layout = GetLayoutClass(object);
    float radius;

    if (!layout->active) {
        return 0;
    }
    if (!layout->boundaryEnabled) {
        return 0;
    }
    radius = layout->collision->data->radius * layout->scale + margin;
    if (squareDistance(position, layout->center) < radius * radius) {
        return 1;
    }
    return 0;
}
