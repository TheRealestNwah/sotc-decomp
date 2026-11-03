#ifdef NONMATCHING /* 34 diffs: target keeps the result in v1 with explicit 0/1 stores and re-tests kind 0x280000000 at the end */
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
    char padC[0xC]; CollisionPlane *planes;
    char pad1C[0x18]; char *attributes;
} CollisionResource;
typedef struct { char pad0[0x20]; CollisionResource *resource; } CollisionFile;
typedef struct { char pad0[0x184]; CollisionFile *collision; } LayoutClass;
typedef struct { void *object; unsigned int packed; } CollisionReference;
extern LayoutClass *GetLayoutClass(void *);
static inline int collisionAttributeIndex(CollisionReference *reference)
{
    int nodeIndex = (reference->packed >> 24) & 0x7F;
    int shapeIndex = reference->packed & 0xFFFFFF;
    CollisionResource *resource = GetLayoutClass(reference->object)->collision->resource;
    if ((int)reference->packed < 0) {
        CollisionNode *node = &resource->nodes[nodeIndex];
        if (node->packed != 0)
            return ((PackedCollisionShape *)node->shapes)[shapeIndex].attribute;
        return ((FullCollisionShape *)node->shapes)[shapeIndex].attribute;
    }
    return resource->planes[resource->nodes[nodeIndex].planeIndices[shapeIndex]].attribute;
}
static inline void *attributeAddress(CollisionReference *reference)
{
    CollisionResource *resource = GetLayoutClass(reference->object)->collision->resource;
    int index = collisionAttributeIndex(reference);
    return resource->attributes + index * 16;
}
int CollisionPlaneJudgeCallbackCameraMove(CollisionReference *reference)
{
    unsigned long attr = *(unsigned long *)attributeAddress(reference);
    unsigned long kind = attr & 0xF80000000ULL;
    unsigned long sound = attr & 0x7C000000;
    unsigned long camera = attr & 0x3C0000000000ULL;

    if (kind == 0x280000000ULL) return 1;
    if (camera == 0x200000000000ULL) return 0;
    if (sound == 0x30000000 || sound == 0x34000000 || sound == 0x64000000 || sound == 0x68000000 || sound == 0x6C000000 || sound == 0x24000000) return 0;
    if (kind == 0x300000000ULL || kind == 0x500000000ULL || kind == 0x200000000ULL || kind == 0xB80000000ULL || kind == 0x80000000ULL || kind == 0x280000000ULL) return 0;
    if (camera != 0x80000000000ULL) return 1;
    return 0;
}
#endif
