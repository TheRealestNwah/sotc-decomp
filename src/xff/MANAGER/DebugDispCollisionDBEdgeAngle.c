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
static inline void planeVertices(int *out, CollisionRuntime *runtime, CollisionResource *resource, int nodeIndex, int shapeIndex)
{
    CollisionModel *model = runtime->model;
    func_0009AE78(out, 0, model->geometry, model->nodes, runtime->matrices,
        resource->nodes, resource->vertices,
        &resource->planes[resource->nodes[nodeIndex].planeIndices[shapeIndex]]);
}
extern int RO_001407D8[];
extern char RO_00140800[];
extern void DebugDispCollisionDBEdge();
extern int iosInitKPrintfContext3D(void *, void *, int, int, float, float, float, float);
extern void kprintfContextCentering(void *, const char *, ...);
#ifdef NONMATCHING
/* Parked: 48 words differ (load/scheduling order around the pair loads and 0.5f constant). */
void DebugDispCollisionDBEdgeAngle(CollisionReference *reference, int edge, float angle)
{
    struct { int pair[4] __attribute__((aligned(16))); float point[4]; float ctx[16]; int vertices[4]; } L;
    int *vertices;
    int *pair;
    int nodeIndex;
    int shapeIndex;
    LayoutClass *layout;
    DebugDispCollisionDBEdge();
    shapeIndex = reference->packed & 0xFFFFFF;
    nodeIndex = (reference->packed >> 24) & 0x7F;
    vertices = L.vertices;
    pair = L.pair;
    layout = GetLayoutClass(reference->object);
    if ((int)reference->packed < 0) {
        func_000999E0(vertices, 0, layout, nodeIndex, shapeIndex);
    } else {
        planeVertices(vertices, &layout->runtime, layout->collision->resource, nodeIndex, shapeIndex);
    }
    pair[0] = vertices[edge];
    pair[1] = vertices[RO_001407D8[edge]];
    __asm__ __volatile__(".set noreorder
"
                         "mfc1 $8, %0
"
                         "qmtc2.ni $8, vf7
"
                         "lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vsubx.w vf8, vf0, vf7x
"
                         "vmulax.xyzw ACC, vf5, vf7x
"
                         "vmaddw.xyzw vf9, vf6, vf8w
"
                         "sqc2 vf9, 0x0(%3)
"
                         ".set reorder
"
                         : : "f"(0.5f), "r"(pair[0]), "r"(pair[1]), "r"(L.point) : "memory", "$8");
    if (iosInitKPrintfContext3D(L.ctx, L.point, 0, 1, 1.0f, 1.0f, 1.0f, 1.0f) != 0) {
        kprintfContextCentering(L.ctx, RO_00140800, (int)angle);
    }
}
#else
void DebugDispCollisionDBEdgeAngle(CollisionReference *reference, int edge, float angle);
#endif
