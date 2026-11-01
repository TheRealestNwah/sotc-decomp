typedef int s128 __attribute__((mode(TI)));
typedef struct {
    char pad0[0x54];
    int *planeIndices;
    char pad58[0x38];
} CollisionNode;
typedef struct { char pad0[8]; CollisionNode *nodes; } CollisionResource;
typedef struct { char pad0[0x20]; CollisionResource *resource; } CollisionFile;
typedef struct {
    char pad0[0x154];
    s128 *quaternions;
    char pad158[0x2C];
    CollisionFile *collision;
} LayoutClass;
typedef struct { void *object; unsigned int packed; } CollisionReference;
extern LayoutClass *GetLayoutClass(void *);
static void func_0009E2D8(s128 *, LayoutClass *, int);

void GetCollisionDBQuaternion(s128 *out, CollisionReference *reference)
{
    int nodeIndex = (reference->packed >> 24) & 0x7F;
    int shapeIndex = reference->packed & 0xFFFFFF;
    LayoutClass *layout = GetLayoutClass(reference->object);

    if ((int)reference->packed < 0) {
        *out = layout->quaternions[nodeIndex];
        return;
    }
    func_0009E2D8(out, layout, layout->collision->resource->nodes[nodeIndex].planeIndices[shapeIndex]);
}
