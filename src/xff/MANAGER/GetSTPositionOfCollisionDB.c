#ifdef NONMATCHING /* parked draft: 16 diffs; the Original allocates vp/point/pe1 to s4/s5/s7 (saved-register rotation) and loads the -2e-5 constant before storing *s and *t */
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
typedef struct { char pad0[0x24]; void *nodes; char geometry[0x48]; } CollisionModel;
typedef struct { char pad0[8]; void *matrices; char padC[0x14]; CollisionModel *model; char pad24[0xC]; } CollisionRuntime;
typedef struct { char pad0[0x154]; CollisionRuntime runtime; CollisionFile *collision; } LayoutClass;
typedef struct { void *object; unsigned int packed; } CollisionReference;
extern LayoutClass *GetLayoutClass(void *);
extern void func_0009AE78(void **, int, void *, void *, void *, CollisionNode *, void *, CollisionPlane *);
extern void func_000999E0(void **, int, LayoutClass *, int, int);

static inline void getST(float *s, float *t, Vec4 *a, Vec4 *b, Vec4 *p)
{
    float rs;
    float rt;
    __asm__ __volatile__("lqc2 vf5, 0x0(%2)\n"
                         "lqc2 vf6, 0x0(%3)\n"
                         "lqc2 vf7, 0x0(%4)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf8, vf6, vf5\n"
                         "vsub.w vf8, vf8, vf8\n"
                         "vopmula.xyz ACC, vf8, vf6\n"
                         "vopmsub.xyz vf9, vf6, vf8\n"
                         "vsub.w vf9, vf9, vf9\n"
                         "vaddw.x vf10, vf0, vf0w\n"
                         "vmul.xyz vf11, vf9, vf7\n"
                         "vaddax.x ACC, vf0, vf11x\n"
                         "vmadday.x ACC, vf10, vf11y\n"
                         "vmaddz.x vf10, vf10, vf11z\n"
                         "qmfc2.ni $2, vf10\n"
                         "mtc1 $2, $f2\n"
                         "vaddw.x vf10, vf0, vf0w\n"
                         "vmul.xyz vf11, vf9, vf5\n"
                         "vaddax.x ACC, vf0, vf11x\n"
                         "vmadday.x ACC, vf10, vf11y\n"
                         "vmaddz.x vf10, vf10, vf11z\n"
                         "qmfc2.ni $2, vf10\n"
                         "mtc1 $2, $f3\n"
                         "div.s %0, $f2, $f3\n"
                         "vopmula.xyz ACC, vf8, vf5\n"
                         "vopmsub.xyz vf9, vf5, vf8\n"
                         "vsub.w vf9, vf9, vf9\n"
                         "vaddw.x vf10, vf0, vf0w\n"
                         "vmul.xyz vf11, vf9, vf7\n"
                         "vaddax.x ACC, vf0, vf11x\n"
                         "vmadday.x ACC, vf10, vf11y\n"
                         "vmaddz.x vf10, vf10, vf11z\n"
                         "qmfc2.ni $2, vf10\n"
                         "mtc1 $2, $f2\n"
                         "vaddw.x vf10, vf0, vf0w\n"
                         "vmul.xyz vf11, vf9, vf6\n"
                         "vaddax.x ACC, vf0, vf11x\n"
                         "vmadday.x ACC, vf10, vf11y\n"
                         "vmaddz.x vf10, vf10, vf11z\n"
                         "qmfc2.ni $2, vf10\n"
                         "mtc1 $2, $f3\n"
                         "div.s %1, $f2, $f3\n"
                         : "=f"(rs), "=f"(rt) : "r"(a), "r"(b), "r"(p) : "$2", "$f2", "$f3");
    *s = rs;
    *t = rt;
}

int GetSTPositionOfCollisionDB(float *s, float *t, CollisionReference *reference, Vec4 *point)
{
    Vec4 e1;
    Vec4 e2;
    Vec4 d;
    void *v[4];
    void **vp = v;
    Vec4 *pe1 = &e1;
    Vec4 *pe2 = &e2;
    unsigned int packed = reference->packed;
    int nodeIndex = (packed >> 24) & 0x7F;
    int shapeIndex = packed & 0xFFFFFF;
    LayoutClass *layout = GetLayoutClass(reference->object);

    if ((int)reference->packed < 0) {
        func_000999E0(vp, 0, layout, nodeIndex, shapeIndex);
    } else {
        CollisionResource *resource = layout->collision->resource;
        CollisionRuntime *rt = &layout->runtime;
        int plane = resource->nodes[nodeIndex].planeIndices[shapeIndex];

        func_0009AE78(vp, 0, rt->model->geometry, rt->model->nodes, rt->matrices, resource->nodes,
                      resource->vertices, &resource->planes[plane]);
    }
    __asm__ __volatile__("lqc2 vf29, 0x0(%0)\n" : : "r"(v[1]) : "memory");
    __asm__ __volatile__("lqc2 vf30, 0x0(%0)\n" : : "r"(v[0]) : "memory");
    __asm__ __volatile__("vsub.xyzw vf31, vf29, vf30\n"
                         "sqc2 vf31, 0x0(%0)\n" : : "r"(pe1) : "memory");
    __asm__ __volatile__("lqc2 vf29, 0x0(%0)\n" : : "r"(v[2]) : "memory");
    __asm__ __volatile__("vsub.xyzw vf31, vf29, vf30\n"
                         "sqc2 vf31, 0x0(%0)\n" : : "r"(pe2) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%2)\n"
                         : : "r"(point), "r"(v[0]), "r"(&d) : "memory");
    getST(s, t, pe1, pe2, &d);
    if (*s < -0.00002f)
        return 0;
    if (*t < -0.00002f)
        return 0;
    {
        int r = 1;
        if (*s + *t - 1.0f > 0.00002f)
            r = 0;
        return r;
    }
}
#endif
