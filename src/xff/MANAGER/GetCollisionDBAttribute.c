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
typedef int CollisionAttribute __attribute__((mode(TI)));
void GetCollisionDBAttribute(CollisionAttribute *out, CollisionReference *reference)
{
    *out = *(CollisionAttribute *)attributeAddress(reference);
}
