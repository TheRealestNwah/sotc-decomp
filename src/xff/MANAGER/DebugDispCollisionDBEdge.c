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
extern int *GetGlDebugSw(void);
extern void glBegin(int);
extern void glBlendFunc(int, int);
extern void glColor4f(float, float, float, float);
extern void glEnable(int);
extern void glEnd(void);
extern void glLoadMatrixf(void *);
extern void glVertex4fv(int);
extern void glZOffset(float);
extern void iosDlPopLayer(void);
extern void iosDlPushLayer(int);
extern char UnitMatrix[];
extern int RO_001407D8[];
static inline void planeVertices(int *out, CollisionRuntime *runtime, CollisionResource *resource, int nodeIndex, int shapeIndex)
{
    CollisionModel *model = runtime->model;
    func_0009AE78(out, 0, model->geometry, model->nodes, runtime->matrices,
        resource->nodes, resource->vertices,
        &resource->planes[resource->nodes[nodeIndex].planeIndices[shapeIndex]]);
}

void DebugDispCollisionDBEdge(CollisionReference *reference, int edge)
{
    struct { int pair[4] __attribute__((aligned(16))); int vertices[4]; } L;
    int *v;
    int *p;
    int nodeIndex;
    int shapeIndex;
    LayoutClass *layout;

    if (*GetGlDebugSw() == 0) {
        return;
    }
    glLoadMatrixf(UnitMatrix);
    glEnable(3);
    iosDlPushLayer(0x17);
    glBegin(2);
    glBlendFunc(5, 6);
    glZOffset(1.08f);
    glEnd();
    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    glBegin(8);
    glEnable(7);
    glBlendFunc(5, 1);
    glEnd();
    shapeIndex = reference->packed & 0xFFFFFF;
    nodeIndex = (reference->packed >> 24) & 0x7F;
    v = L.vertices;
    p = L.pair;
    layout = GetLayoutClass(reference->object);
    if (reference->packed & 0x80000000) {
        func_000999E0(v, 0, layout, nodeIndex, shapeIndex);
    } else {
        planeVertices(v, &layout->runtime, layout->collision->resource, nodeIndex, shapeIndex);
    }
    { int *q = v + edge; p[0] = *q; }
    { int *q = v + RO_001407D8[edge]; p[1] = *q; }
    glBegin(1);
    glVertex4fv(L.pair[0]);
    glVertex4fv(L.pair[1]);
    glEnd();
    glBegin(8);
    glBlendFunc(5, 6);
    glEnd();
    glBegin(8);
    glZOffset(1.0f);
    glEnable(8);
    glBlendFunc(5, 6);
    glEnd();
    iosDlPopLayer();
    glEnable(3);
}
