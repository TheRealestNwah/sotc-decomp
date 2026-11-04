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
typedef struct { void *object; unsigned int packed; int edge; } CollisionReference;
extern LayoutClass *GetLayoutClass(void *);
extern void func_000999E0(int *, void *, LayoutClass *, int, int);
extern void func_0009AE78(int *, void *, void *, void *, void *, CollisionNode *, void *, CollisionPlane *);
static inline void planeVertices(int *out, CollisionRuntime *runtime, CollisionResource *resource, int nodeIndex, int shapeIndex)
{
    CollisionModel *model = runtime->model;
    func_0009AE78(out, 0, model->geometry, model->nodes, runtime->matrices,
        resource->nodes, resource->vertices,
        &resource->planes[resource->nodes[nodeIndex].planeIndices[shapeIndex]]);
}
extern int RO_001407D8[];
static inline void edgePoints(int *out, CollisionReference *reference)
{
    int vertices[4];
    int nodeIndex = (reference->packed >> 24) & 0x7F;
    int shapeIndex = reference->packed & 0xFFFFFF;
    int edge = reference->edge;
    LayoutClass *layout = GetLayoutClass(reference->object);
    if ((int)reference->packed < 0) {
        func_000999E0((int *)vertices, 0, layout, nodeIndex, shapeIndex);
    } else {
        planeVertices((int *)vertices, &layout->runtime, layout->collision->resource, nodeIndex, shapeIndex);
    }
    out[0] = vertices[edge];
    out[1] = vertices[RO_001407D8[edge]];
}
void GetCollisionEdgePositionWithS(float *out, CollisionReference *reference, float t)
{
    int pair[2];
    edgePoints(pair, reference);
    __asm__ __volatile__(".set noreorder\n"
                         "mfc1 $8, %0\n"
                         "qmtc2.ni $8, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyzw ACC, vf5, vf7x\n"
                         "vmaddw.xyzw vf9, vf6, vf8w\n"
                         "sqc2 vf9, 0x0(%3)\n"
                         ".set reorder\n"
                         : : "f"(t), "r"(pair[0]), "r"(pair[1]), "r"(out) : "memory", "$8");
}
