typedef struct { char pad0[0x30]; int attribute; } FullCollisionShape;
typedef struct { unsigned short attribute; char pad2[0x12]; } PackedCollisionShape;
typedef struct { char pad0[0x3C]; int attribute; } CollisionPlane;
typedef struct {
    char pad0[8];
    unsigned char packed;
    char pad9[0xB];
    void *shapes;
    char pad18[0x3C];
    int *planeIndices;
    char pad58[0x38];
} CollisionNode;
typedef struct {
    char pad0[8]; CollisionNode *nodes;
    char padC[8]; void *vertices; CollisionPlane *planes;
    char pad1C[0x18]; char *attributes;
} CollisionResource;
typedef struct { char pad0[0x20]; CollisionResource *resource; } CollisionFile;
typedef struct { char pad0[0x24]; void *nodes; char geometry[16]; } CollisionModel;
typedef struct { char pad0[8]; void *matrices; char padC[0x14]; CollisionModel *model; char pad24[0xC]; } CollisionRuntime;
typedef struct { char pad0[0x154]; CollisionRuntime runtime; CollisionFile *collision; } LayoutClass;
typedef struct { void *object; unsigned int packed; } CollisionReference;
typedef struct { void *object; unsigned int packed; } CollisionNext;
extern LayoutClass *GetLayoutClass(void *);
#ifdef NONMATCHING
/* Parked: 100 words differ (callee-saved register assignment of out/reference). */
int GetCollisionDBNext3Direct(CollisionNext *out0, CollisionReference *reference)
{
    unsigned char hi = ((unsigned char *)reference)[7];
    int nodeIndex;
    CollisionResource *resource = GetLayoutClass(reference->object)->collision->resource;
    int shapeIndex;
    unsigned int packed;
    int i;
    int any;
    int ok;
    CollisionNext *dst;
    nodeIndex = hi & 0x7F;
    if (resource->nodes[nodeIndex].packed != 0) {
        unsigned short *p;
        packed = reference->packed;
        nodeIndex = packed >> 24;
        resource = GetLayoutClass(reference->object)->collision->resource;
        shapeIndex = packed & 0xFFFFFF;
        nodeIndex &= 0x7F;
        p = (unsigned short *)((char *)resource->nodes[nodeIndex].shapes + shapeIndex * 0x14 + 8);
        any = 0;
        dst = out0;
        for (i = 2; i != -1; i--) {
            ok = 0;
            if (!(p[0] & 0x8000)) {
                dst->object = reference->object;
                ok = 1;
                dst->packed = p[1] | 0x80000000;
            }
            if (ok == 0)
                dst->object = 0;
            else
                any = 1;
            p += 2;
            dst++;
        }
        return any;
    } else {
        int *p;
        packed = reference->packed;
        nodeIndex = packed >> 24;
        resource = GetLayoutClass(reference->object)->collision->resource;
        shapeIndex = packed & 0xFFFFFF;
        nodeIndex &= 0x7F;
        if ((int)reference->packed < 0) {
            p = (int *)((char *)resource->nodes[nodeIndex].shapes + shapeIndex * 0x34 + 0xC);
        } else {
            p = (int *)((char *)&resource->planes[resource->nodes[nodeIndex].planeIndices[shapeIndex]] + 0x18);
        }
        any = 0;
        dst = out0;
        for (i = 2; i != -1; i--) {
            int a = p[1];
            ok = 0;
            if (a != -1) {
                int v;
                dst->object = reference->object;
                v = p[2];
                if (v < 0)
                    dst->packed = ((v & 0x7FFFFFFF) << 24) | a | 0x80000000;
                else
                    dst->packed = (v << 24) | a;
                ok = 1;
            }
            if (ok == 0)
                dst->object = 0;
            else
                any = 1;
            p += 3;
            dst++;
        }
        return any;
    }
}
#else
int GetCollisionDBNext3Direct(CollisionNext *out, CollisionReference *reference);
#endif
