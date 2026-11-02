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
extern void func_0009AE78(int *, void *, void *, void *, void *, CollisionNode *, void *, CollisionPlane *);
static inline void boundarySub(void *a0, void *a1, void *a2, void *a3, float f0)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf4, 0x0(%0)\n"
        "lqc2 vf5, 0x0(%1)\n"
        "lqc2 vf6, 0x0(%2)\n"
        "mfc1 $8, %3\n"
        "qmtc2.ni $8, vf8\n"
        "vadd.xyz vf7, vf4, vf5\n"
        "vadd.xyz vf7, vf7, vf6\n"
        "vmulx.xyz vf7, vf7, vf8x\n"
        "vsub.xyz vf4, vf4, vf7\n"
        "vmul.xyz vf4, vf4, vf4\n"
        "vaddy.x vf4, vf4, vf4y\n"
        "vaddz.x vf4, vf4, vf4z\n"
        "vsub.xyz vf5, vf5, vf7\n"
        "vmul.xyz vf5, vf5, vf5\n"
        "vaddy.x vf5, vf5, vf5y\n"
        "vaddz.x vf5, vf5, vf5z\n"
        "vmaxx.x vf8, vf4, vf5x\n"
        "vsub.xyz vf6, vf6, vf7\n"
        "vmul.xyz vf6, vf6, vf6\n"
        "vaddy.x vf6, vf6, vf6y\n"
        "vaddz.x vf6, vf6, vf6z\n"
        "vmaxx.x vf8, vf8, vf6x\n"
        "vmulx.w vf7, vf0, vf8x\n"
        "sqc2 vf7, 0x0(%4)\n"
        ".set reorder\n"
        : : "r"(a1), "r"(a2), "r"(a3), "f"(f0), "r"(a0) : "memory", "$8");
}

void CalcCollisionMultiDepSurfBoundary(void *out, LayoutClass *layout, int plane)
{
    int vertices[4];
    CollisionRuntime *runtime = &layout->runtime;
    CollisionResource *resource = layout->collision->resource;
    CollisionModel *model = runtime->model;

    func_0009AE78(vertices, 0, model->geometry, model->nodes, runtime->matrices,
        resource->nodes, resource->vertices, &resource->planes[plane]);
    boundarySub(out, (void *)vertices[0], (void *)vertices[1], (void *)vertices[2], 1.0f / 3.0f);
}
