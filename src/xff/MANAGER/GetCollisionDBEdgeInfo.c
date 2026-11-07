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
typedef struct { void *object; unsigned int packed; int index; int value; } CollisionEdgeInfo;
extern LayoutClass *GetLayoutClass(void *);
#ifdef NONMATCHING
/* Parked: 86 words differ (register allocation/scheduling); permuter found no zero. */
void GetCollisionDBEdgeInfo(CollisionEdgeInfo *out, CollisionReference *reference)
{
    int nodeIndex = ((unsigned char *)reference)[7] & 0x7F;
    CollisionResource *resource = GetLayoutClass(reference->object)->collision->resource;
    int shapeIndex;
    int i;
    if (resource->nodes[nodeIndex].packed != 0) {
        unsigned short *p;
        shapeIndex = reference->packed & 0xFFFFFF;
        nodeIndex = (reference->packed >> 24) & 0x7F;
        resource = GetLayoutClass(reference->object)->collision->resource;
        p = (unsigned short *)((char *)resource->nodes[nodeIndex].shapes + shapeIndex * 0x14 + 8);
        for (i = 0; i < 3; i++) {
            out->object = reference->object;
            out->index = i;
            out->packed = reference->packed;
            out->value = *p & 0x7FFF;
            p += 2;
            out++;
        }
    } else {
        int *p;
        shapeIndex = reference->packed & 0xFFFFFF;
        nodeIndex = (reference->packed >> 24) & 0x7F;
        resource = GetLayoutClass(reference->object)->collision->resource;
        if ((int)reference->packed < 0) {
            p = (int *)((char *)resource->nodes[nodeIndex].shapes + shapeIndex * 0x34 + 0xC);
        } else {
            p = (int *)((char *)&resource->planes[resource->nodes[nodeIndex].planeIndices[shapeIndex]] + 0x18);
        }
        for (i = 0; i < 3; i++) {
            out->object = reference->object;
            out->index = i;
            out->packed = reference->packed;
            out->value = *p;
            p += 3;
            out++;
        }
    }
}
#else
void GetCollisionDBEdgeInfo(CollisionEdgeInfo *out, CollisionReference *reference);
#endif
