/* Walks every shape and plane of a layout object's collision resource and returns 1 when judge accepts one's attribute. */
typedef struct { char pad0[0x30]; int attribute; } FullCollisionShape;
typedef struct { unsigned short attribute; char pad2[0x12]; } PackedCollisionShape;
typedef struct { char pad0[0x3C]; int attribute; } CollisionPlane;
typedef struct {
    char pad0[8];
    unsigned char packed;
    char pad9[7];
    int shapeCount;
    void *shapes;
    char pad18[0x38];
    int planeCount;
    int *planeIndices;
    char pad58[0x38];
} CollisionNode;
typedef struct {
    char pad0[4]; int nodeCount; CollisionNode *nodes;
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
    if (reference->packed & 0x80000000) {
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
int GetLayoutObjCollisionDBWithTargetAttributeJudgeFunc(CollisionReference *ref, void *obj0, int (*judge)(void *))
{
    /* Pinned: gcc otherwise gives obj $s6 and the attribute resource $s5, the reverse of the Original. */
    register void *obj asm("$21") = obj0;
    LayoutClass *lc;
    CollisionResource *res;
    CollisionNode *node;
    int count, n, i, m;

    lc = GetLayoutClass(obj);
    if (lc != 0) {
    res = lc->collision->resource;
    if (res != 0) {
    count = res->nodeCount;
    node = res->nodes;
    for (n = 0; n < count; n++, node++) {
        m = node->shapeCount;
        for (i = 0; i < m; i++) {
            ref->object = obj;
            ref->packed = (n << 24) | i | 0x80000000;
            if (judge(attributeAddress(ref)))
                return 1;
        }
        m = node->planeCount;
        for (i = 0; i < m; i++) {
            ref->packed = (n << 24) | i;
            ref->object = obj;
            if (judge(attributeAddress(ref)))
                return 1;
        }
    }
    }}
    return 0;
}
