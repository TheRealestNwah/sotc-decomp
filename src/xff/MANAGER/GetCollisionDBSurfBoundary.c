typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { char pad0[0x3C]; int attribute; } CollisionPlane;
typedef struct {
    char pad0[0x54];
    int *planeIndices;
    char pad58[0x38];
} CollisionNode;
typedef struct {
    char pad0[8]; CollisionNode *nodes;
    char padC[8]; void *vertices; CollisionPlane *planes;
} CollisionResource;
typedef struct { char pad0[0x20]; CollisionResource *resource; } CollisionFile;
typedef struct { char pad0[8]; unsigned char *flags; char padC[8]; s128 *values; } SurfCache;
typedef struct { char pad0[0x24]; void *nodes; char geometry[0x48]; SurfCache cache; } CollisionModel;
typedef struct { char pad0[8]; void *matrices; char padC[0x14]; CollisionModel *model; char pad24[0xC]; } CollisionRuntime;
typedef struct { char pad0[0x154]; CollisionRuntime runtime; CollisionFile *collision; } LayoutClass;
typedef struct { void *object; unsigned int packed; } CollisionReference;
extern LayoutClass *GetLayoutClass(void *);
extern void func_0009AE78(void **, int, void *, void *, void *, CollisionNode *, void *, CollisionPlane *);
extern s128 *getLayoutClassCollisionIndepSurfBoundary(LayoutClass *, int, int);
extern void EntryModifiedManager(void *, int);

#ifdef NONMATCHING
/* Parked: 2 words differ (the Original moves the float through $t0 for mfc1/qmtc2, ours uses $v0). */
void GetCollisionDBSurfBoundary(Vec4 *out, CollisionReference *reference)
{
    unsigned int packed = reference->packed;
    int nodeIndex = (packed >> 24) & 0x7F;
    int shapeIndex = packed & 0xFFFFFF;
    LayoutClass *layout = GetLayoutClass(reference->object);

    if ((int)reference->packed < 0) {
        out->q = *getLayoutClassCollisionIndepSurfBoundary(layout, nodeIndex, shapeIndex);
        out->f[3] = out->f[3] * out->f[3];
    } else {
        CollisionResource *resource = layout->collision->resource;
        SurfCache *cache = &layout->runtime.model->cache;
        int plane = resource->nodes[nodeIndex].planeIndices[shapeIndex];
        s128 *entry = &cache->values[plane];

        if (cache->flags[plane] == 0) {
            void *v[4];
            float third;
            CollisionRuntime *rt = &layout->runtime;

            func_0009AE78(v, 0, rt->model->geometry, rt->model->nodes, rt->matrices, resource->nodes,
                          resource->vertices, &resource->planes[plane]);
            third = 1.0f / 3.0f;
            __asm__ __volatile__("lqc2 vf4, 0x0(%0)\n"
                                 "lqc2 vf5, 0x0(%1)\n"
                                 "lqc2 vf6, 0x0(%2)\n"
                                 : : "r"(v[0]), "r"(v[1]), "r"(v[2]) : "memory");
            __asm__ __volatile__("qmtc2.ni %0, vf8\n"
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
                                 "sqc2 vf7, 0x0(%1)\n"
                                 : : "r"(third), "r"(entry) : "memory");
            EntryModifiedManager(cache, plane);
        }
        out->q = *entry;
    }
}
#else
void GetCollisionDBSurfBoundary(Vec4 *out, CollisionReference *reference);
#endif
