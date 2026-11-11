/* Parked: CB variant of SlideCollisionFinder4D (same inlined collision-attribute decode); see that file for notes. */
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
typedef int s128 __attribute__((mode(TI)));
typedef struct { char pad0[0x20]; CollisionReference ref; char tail[0x28]; } CollisionHit;
typedef struct { char b[0x30]; } Blk30;
typedef struct { char b[0x30]; int have; } HitCopy;
typedef struct { char pad0[0x30]; CollisionHit best; int have; } Finder;
extern int ClipCollisionFinderWithKeep4DSlopeLimit(CollisionHit *, void *, void *, int, int, float, float);
extern int ClipCollisionFinderWithKeep4DSlopeLimitCB(CollisionHit *, void *, void *, int, int, float, float);
extern int func_000A43F8(void *, void *, void *, int, int, float, float, int, int);

#ifdef NONMATCHING
int SlideCollisionFinder4DCB(char *finder, s128 *p, s128 *q, int a3, int t0, int cb, float f12, float f13)
{
    CollisionHit hit;
    s128 pc = *p;
    s128 qc = *q;
    HitCopy *keep = (HitCopy *)(finder + 0x30);
    int ok;

    keep->have = 0;
    if (cb != 0)
        ok = ClipCollisionFinderWithKeep4DSlopeLimitCB(&hit, &pc, &qc, a3, t0, f12, f13);
    else
        ok = ClipCollisionFinderWithKeep4DSlopeLimit(&hit, &pc, &qc, a3, t0, f12, f13);
    if (ok == 0)
        return 0;
    if (keep->have == 0) {
        if ((int)(*(unsigned long *)attributeAddress(&hit.ref) & 1) != 0) {
            *(Blk30 *)keep = *(Blk30 *)&hit;
            keep->have = 1;
        }
    }
    return func_000A43F8(finder, &hit, &qc, a3, t0, f12, f13, 0, 0);
}
#else
extern int SlideCollisionFinder4DCB(char *, s128 *, s128 *, int, int, int, float, float);
#endif
