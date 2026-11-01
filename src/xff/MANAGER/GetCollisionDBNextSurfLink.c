typedef struct { char pad0[0xC]; char link[0x28]; } CollisionShape;
typedef struct { char pad0[0x18]; char link[0x28]; } CollisionPlane;
typedef struct {
    char pad0[0x14];
    CollisionShape *shapes;
    char pad18[0x3C];
    int *planeIndices;
    char pad58[0x38];
} CollisionNode;
typedef struct {
    char pad0[8]; CollisionNode *nodes;
    char padC[0xC]; CollisionPlane *planes;
} CollisionResource;
typedef struct { char pad0[0x20]; CollisionResource *resource; } CollisionFile;
typedef struct { char pad0[0x184]; CollisionFile *collision; } LayoutClass;
typedef struct { void *object; unsigned int packed; } CollisionReference;
extern LayoutClass *GetLayoutClass(void *);

void *GetCollisionDBNextSurfLink(CollisionReference *reference)
{
    int nodeIndex = (reference->packed >> 24) & 0x7F;
    int shapeIndex = reference->packed & 0xFFFFFF;
    CollisionResource *resource = GetLayoutClass(reference->object)->collision->resource;

    if ((int)reference->packed < 0) {
        CollisionNode *node = &resource->nodes[nodeIndex];
        return node->shapes[shapeIndex].link;
    }
    return resource->planes[resource->nodes[nodeIndex].planeIndices[shapeIndex]].link;
}
