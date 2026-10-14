typedef int s128 __attribute__((mode(TI)));

typedef union {
    s128 q;
    float f[4];
    int i[4];
} Vec4;

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
    char pad94[0xA0];
    Vec4 *center;
    char pad138[0x4C];
    CollisionInfo *collision;
} LayoutClass;

typedef struct {
    Vec4 center;
} Boundary;

extern Vec4 ZeroVector;

int GetLayoutClassCollisionBoundaryInfo(Boundary *out, LayoutClass *layout)
{
    CollisionInfo *col = layout->collision;

    if (col != 0) {
        BoundaryData *bd = col->data;

        out->center.q = layout->center->q;
        out->center.f[3] = bd->radius * layout->scale;
        return 0;
    }
    out->center.q = ZeroVector.q;
    return -1;
}
