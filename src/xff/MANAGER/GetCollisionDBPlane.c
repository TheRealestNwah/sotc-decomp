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
typedef struct { char pad0[8]; unsigned char *flags; char padC[8]; long long (*values)[2]; } PlaneCache;
extern LayoutClass *GetLayoutClass(void *);
extern void func_000999E0(int *, int *, LayoutClass *, int, int);
extern void func_0009AE78(int *, int *, void *, void *, void *, CollisionNode *, void *, CollisionPlane *);
extern void EntryModifiedManager(void *, int);
static inline void computePlane(float *out, int *v)
{
    __asm__ __volatile__("lqc2 vf29, 0x0(%0)
" : : "r"(v[0]) : "memory");
    __asm__ __volatile__("lqc2 vf30, 0x0(%0)
vsub.xyzw vf31, vf29, vf30
vmove.xyzw vf18, vf31
vmove.xyzw vf29, vf30
"
                         : : "r"(v[1]) : "memory");
    __asm__ __volatile__("lqc2 vf30, 0x0(%0)
vsub.xyzw vf31, vf29, vf30
vmove.xyzw vf29, vf18
vmove.xyzw vf30, vf31
"
                         "vopmula.xyz ACC, vf29, vf30
vopmsub.xyz vf31, vf30, vf29
vsub.w vf31, vf31, vf31
vmove.xyzw vf29, vf31
"
                         "vmul.xyz vf7, vf29, vf29
vmulax.w ACC, vf0, vf7x
vmadday.w ACC, vf0, vf7y
vmaddz.w vf7, vf0, vf7z
"
                         "vrsqrt Q, vf0w, vf7w
vwaitq
vmulq.xyz vf29, vf29, Q
vmove.xyzw vf31, vf29
sqc2 vf31, 0x0(%1)
"
                         : : "r"(v[2]), "r"(out) : "memory");
    __asm__ __volatile__("lqc2 vf4, 0x0(%0)
lqc2 vf5, 0x0(%1)
vmul.xyz vf5, vf4, vf5
vaddy.x vf5, vf5, vf5y
vaddz.x vf5, vf5, vf5z
"
                         "vsubw.xyzw vf6, vf0, vf0w
vsubx.w vf4, vf6, vf5x
sqc2 vf4, 0x0(%0)
"
                         : : "r"(out), "r"(v[0]) : "memory");
}
#ifdef NONMATCHING
/* Parked: ~103 words differ (frame size, hoisting of node index math). */
float *GetCollisionDBPlane(CollisionReference *reference)
{
    int nodeIndex = (reference->packed >> 24) & 0x7F;
    int shapeIndex = reference->packed & 0xFFFFFF;
    LayoutClass *layout = GetLayoutClass(reference->object);
    float *entry;
    PlaneCache *cache;
    int v[4];
    int aux[4];
    int v2[4];
    int aux2[4];
    if ((int)reference->packed < 0) {
        cache = (PlaneCache *)((char *)((CollisionModel *)layout->runtime.model)->nodes + nodeIndex * 0x60 + 0x30);
        entry = (float *)&cache->values[shapeIndex];
        if (cache->flags[shapeIndex] == 0) {
            func_000999E0(v, aux, layout, nodeIndex, shapeIndex);
            computePlane(entry, v);
            EntryModifiedManager(cache, shapeIndex);
        }
    } else {
        CollisionResource *resource = layout->collision->resource;
        int plane = resource->nodes[nodeIndex].planeIndices[shapeIndex];
        cache = (PlaneCache *)((char *)layout->runtime.model + 0x58);
        entry = (float *)&cache->values[plane];
        if (cache->flags[plane] == 0) {
            CollisionModel *model = layout->runtime.model;
            func_0009AE78(v2, aux2, model->geometry, model->nodes, layout->runtime.matrices,
                resource->nodes, resource->vertices, &resource->planes[plane]);
            computePlane(entry, v2);
            EntryModifiedManager(cache, plane);
        }
    }
    return entry;
}
#else
float *GetCollisionDBPlane(CollisionReference *reference);
#endif
