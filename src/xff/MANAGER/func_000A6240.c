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
extern LayoutClass *GetLayoutClass(void *);
extern void func_000999E0(int *, void *, LayoutClass *, int, int);
extern void func_0009AE78(int *, void *, void *, void *, void *, CollisionNode *, void *, CollisionPlane *);
extern void DebugDispTriangleVectorPointerArray(int *, float, float, float, float, int);
extern int iosInitKPrintfContext3D(void *, void *, int, float, float, float, float, int);
extern void kprintfContextCentering(void *, const char *, ...);
extern char RO_001407F8[];
static inline void planeVertices(int *out, CollisionRuntime *runtime, CollisionResource *resource, int nodeIndex, int shapeIndex)
{
    CollisionModel *model = runtime->model;
    func_0009AE78(out, 0, model->geometry, model->nodes, runtime->matrices,
        resource->nodes, resource->vertices,
        &resource->planes[resource->nodes[nodeIndex].planeIndices[shapeIndex]]);
}


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
static void func_000A6240(CollisionReference *reference, int highlight, int number, float r1, float g1, float b1,
    float r2, float g2, float b2, float a)
{
    struct { int vertices[4]; char ctx[0x40]; float center[4]; } L;
    int shapeIndex = reference->packed & 0xFFFFFF;
    int nodeIndex = (reference->packed >> 24) & 0x7F;
    int drawn = 0;
    LayoutClass *layout = GetLayoutClass(reference->object);

    if (reference->packed & 0x80000000) {
        func_000999E0(L.vertices, 0, layout, nodeIndex, shapeIndex);
    } else {
        planeVertices(L.vertices, &layout->runtime, layout->collision->resource, nodeIndex, shapeIndex);
    }
    if (highlight) {
        unsigned long etc = *(unsigned long *)attributeAddress(reference) & 0xF80000000UL;
        drawn = 1;
        if (etc == 0x200000000UL || etc == 0xB80000000UL) {
            DebugDispTriangleVectorPointerArray(L.vertices, 1.0f, 1.0f, 0.0f, a, 1);
        } else {
            drawn = 0;
        }
    }
    if (!drawn) {
        if (reference->packed & 0x80000000) {
            DebugDispTriangleVectorPointerArray(L.vertices, r1, g1, b1, a, 1);
        } else {
            DebugDispTriangleVectorPointerArray(L.vertices, r2, g2, b2, a, 1);
        }
    }
    if (number >= 0) {
        float *c = L.center;
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vadd.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(c), "r"(L.vertices[0]), "r"(L.vertices[1]) : "memory");
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vadd.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(c), "r"(c), "r"(L.vertices[2]) : "memory");
        __asm__ __volatile__("mfc1 $2, %1\n"
                             "lqc2 vf5, 0x0(%0)\n"
                             "qmtc2.ni $2, vf6\n"
                             "vmulx.xyz vf5, vf5, vf6x\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(c), "f"(0.33333331f) : "memory", "$2");
        if (iosInitKPrintfContext3D(L.ctx, c, 0, 1.0f, 1.0f, 1.0f, 1.0f, 1)) {
            kprintfContextCentering(L.ctx, RO_001407F8, number);
        }
    }
}
