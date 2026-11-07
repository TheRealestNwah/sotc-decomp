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
typedef struct { char pad0[8]; unsigned char *flags; char padC[8]; long long (*values)[2]; } SurfCache;
extern LayoutClass *GetLayoutClass(void *);
extern void func_0009AE78(int *, void *, void *, void *, void *, CollisionNode *, void *, CollisionPlane *);
extern long long *getLayoutClassCollisionIndepSurfBoundary(LayoutClass *, int, int, LayoutClass *);
extern void EntryModifiedManager(void *, int);
typedef int s128 __attribute__((mode(TI)));
#ifdef NONMATCHING
/* Parked: first draft, register allocation differs (101 words). */
void GetCollisionDBSurfBoundary(float *out, CollisionReference *reference)
{
    int nodeIndex = (reference->packed >> 24) & 0x7F;
    int shapeIndex = reference->packed & 0xFFFFFF;
    LayoutClass *layout = GetLayoutClass(reference->object);
    if ((int)reference->packed < 0) {
        *(s128 *)out = *(s128 *)getLayoutClassCollisionIndepSurfBoundary(layout, nodeIndex, shapeIndex, layout);
        out[3] = out[3] * out[3];
    } else {
        SurfCache *cache = (SurfCache *)((char *)layout->runtime.model + 0x70);
        CollisionResource *resource = layout->collision->resource;
        int plane = resource->nodes[nodeIndex].planeIndices[shapeIndex];
        s128 *entry = (s128 *)&cache->values[plane];
        if (cache->flags[plane] == 0) {
            int v[4];
            planeVertices(v, &layout->runtime, resource, nodeIndex, shapeIndex);
            __asm__ __volatile__("lqc2 vf4, 0x0(%0)
lqc2 vf5, 0x0(%1)
lqc2 vf6, 0x0(%2)
"
                                 : : "r"(v[0]), "r"(v[1]), "r"(v[2]) : "memory");
            __asm__ __volatile__("qmtc2.ni %0, vf8
vadd.xyz vf7, vf4, vf5
vadd.xyz vf7, vf7, vf6
vmulx.xyz vf7, vf7, vf8x
"
                                 "vsub.xyz vf4, vf4, vf7
vmul.xyz vf4, vf4, vf4
vaddy.x vf4, vf4, vf4y
vaddz.x vf4, vf4, vf4z
"
                                 "vsub.xyz vf5, vf5, vf7
vmul.xyz vf5, vf5, vf5
vaddy.x vf5, vf5, vf5y
vaddz.x vf5, vf5, vf5z
"
                                 "vmaxx.x vf8, vf4, vf5x
vsub.xyz vf6, vf6, vf7
vmul.xyz vf6, vf6, vf6
vaddy.x vf6, vf6, vf6y
"
                                 "vaddz.x vf6, vf6, vf6z
vmaxx.x vf8, vf8, vf6x
vmulx.w vf7, vf0, vf8x
sqc2 vf7, 0x0(%1)
"
                                 : : "r"(1.0f / 3.0f), "r"(entry) : "memory");
            EntryModifiedManager(cache, plane);
        }
        *(s128 *)out = *entry;
    }
}
#else
void GetCollisionDBSurfBoundary(float *out, CollisionReference *reference);
#endif
