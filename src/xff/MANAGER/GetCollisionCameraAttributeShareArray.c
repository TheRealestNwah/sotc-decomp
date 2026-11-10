/* ~58 diffs, 4 words longer (150 vs 146). Fetches the collision GP db entry, and when the collision resource version is >= 5 with a camera attribute table (res+0x44) decodes the camera-attribute short index of the hit shape (packed node/shape reference, either from the node shape array at node+0x34 or via the plane index table at res+0x54) and writes (index << 15) plus 1.0f as the share record, returning 1; otherwise falls back to the generic attribute word masked with 0x1F8000. Remaining diffs: the original assigns -1 to the index in the delay slot of the owner test and shifts the int index before widening (sll then sd), and orders the first resource-pointer loads a few instructions apart; ours widens first (any (long)(int) cast variant jumped to 122). */
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
typedef struct { void *object; unsigned int packed; } GP;
extern GP *GetGeometryPointerCollisionDB(char *);

#ifdef NONMATCHING
int GetCollisionCameraAttributeShareArray(long *out, char *gp)
{
    GP *db = GetGeometryPointerCollisionDB(gp);
    CollisionResource *res = GetLayoutClass(db->object)->collision->resource;
    int r;
    int index;

    r = -1;
    if (*(int *)res >= 5 && *(int *)((char *)res + 0x44) != 0) {
        index = -1;
        if (db->object != 0) {
            CollisionResource *rr;
            int nodeIndex = (db->packed >> 24) & 0x7F;
            int shapeIndex = db->packed & 0xFFFFFF;

            rr = GetLayoutClass(db->object)->collision->resource;
            if ((int)db->packed < 0)
                index = ((unsigned short *)*(char **)((char *)&rr->nodes[nodeIndex] + 0x34))[shapeIndex];
            else
                index = ((unsigned short *)*(char **)((char *)rr + 0x54))[rr->nodes[nodeIndex].planeIndices[shapeIndex]];
        }
        if (out != 0) {
            *out = (long)index << 15;
            ((float *)out)[2] = 1.0f;
        }
        r = 1;
    }
    if (r < 0) {
        GP *d2 = GetGeometryPointerCollisionDB(gp);
        long v;

        v = *(unsigned long *)attributeAddress((CollisionReference *)d2) & 0x1F8000;
        ((float *)out)[2] = 1.0f;
        *out = v;
        return (int)v;
    }
    return r;
}
#endif
