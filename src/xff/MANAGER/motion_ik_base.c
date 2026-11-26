extern void *DldSysUndefSymbol;
typedef struct {
    char pad[0x20];
    float q[4];
    char pad2[0x10];
} MotNode;
typedef struct {
    int pad[2];
    MotNode *nodes;
} MotBase;
typedef struct {
    int pad;
    float (*quats)[4];
    int pad2[2];
    MotBase *base;
    int index;
    unsigned int *ref;
} MotWork;
typedef struct {
    int pad[3];
    int size;
} ResInfo;
static inline char *resourceModule(unsigned int *reference)
{
    unsigned int offset = *reference & 0x3FFFF;
    if (offset)
        return *(char **)((char *)reference - offset);
    return 0;
}
static inline char *resourceEntry(unsigned int *reference)
{
    char *module = resourceModule(reference);
    if (module && module != DldSysUndefSymbol)
        return *(char **)(module + 0x10) + ((*reference >> 18) & 0xFFF) * (*(ResInfo **)(module + 8))->size;
    return 0;
}
static inline void quatMul(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "lqc2 vf12, 0x0(%2)\n"
                         "vmul.xyzw vf13, vf11, vf12\n"
                         "vaddy.x vf13, vf13, vf13y\n"
                         "vaddz.x vf13, vf13, vf13z\n"
                         "vsubx.w vf13, vf13, vf13x\n"
                         "vmulw.xyz vf14, vf12, vf11w\n"
                         "vmulw.xyz vf15, vf11, vf12w\n"
                         "vopmula.xyz ACC, vf12, vf11\n"
                         "vopmsub.xyz vf16, vf11, vf12\n"
                         "vadd.xyz vf13, vf14, vf15\n"
                         "vadd.xyz vf13, vf13, vf16\n"
                         "sqc2 vf13, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}
inline void update_node_by_quater_motion_ik_base(MotWork **pw, float *q)
{
    MotWork *w = *pw;
    int idx = w->index;
    char *entry = resourceEntry(w->ref);

    if (*(int *)(entry + 0x10) == 0) {
        quatMul(w->quats[idx], w->base->nodes[idx].q, q);
    } else {
        quatMul(w->quats[idx], w->quats[idx], q);
    }
}
typedef union { float f[4]; int q __attribute__((mode(TI))); } Vec4;
typedef struct { Vec4 vectors[2]; Vec4 rotation; Vec4 last; } NodeGeometry;
typedef struct { int unknown0, unknown4; NodeGeometry *nodes; } GeometryTable;
typedef struct {
    int unknown0;
    Vec4 *quaternions;
    int unknown8, unknownC;
    GeometryTable *geometry;
    int node;
    unsigned int *resource;
} MotionIkWork;
typedef struct { MotionIkWork *work; } MotionIkBase;
extern Vec4 IdentityQuaternion;
extern void DivQuaternion(Vec4 *, Vec4 *, Vec4 *);
static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}
static inline void getNodeQuaternion(Vec4 *out, MotionIkBase *base)
{
    MotionIkWork *work = base->work;
    int node = work->node;
    if (*(int *)(dldResolve(work->resource) + 0x10) == 0)
        DivQuaternion(out, &work->quaternions[node], &work->geometry->nodes[node].rotation);
    else
        out->q = IdentityQuaternion.q;
}
extern void GetEulerYXZFromQuaternion(void *, void *);
extern void GetEulerZXYFromQuaternion(void *, void *);
extern void GetQuaternionByEulerYXZ(float *, float, float, float);
extern void GetQuaternionByEulerZXY(float *, float, float, float);

void convert_from_quater_to_rotXYZ_motion_ik_base(void *a, void *b, char **c);
void convert_from_quater_to_rotXYZ_direct_motion_ik_base(void *rot, void *q, int mode);
void convert_from_rotXYZ_to_quater_motion_ik_base(void *a, void *b, char **c);
void convert_from_rotXYZ_to_quater_direct_motion_ik_base(float *q, float *r, int order);

void update_node_by_rotXYZ_motion_ik_base(MotWork **pw, void *rot)
{
    float q[4] __attribute__((aligned(16)));

    convert_from_rotXYZ_to_quater_motion_ik_base(q, rot, pw);
    update_node_by_quater_motion_ik_base(pw, q);
}

void get_animation_designer_node_quater_motion_ik_base(Vec4 *out, MotionIkBase *base)
{
    MotionIkWork *work = base->work;
    int node = work->node;
    if (*(int *)(dldResolve(work->resource) + 0x10) == 0)
        DivQuaternion(out, &work->quaternions[node], &work->geometry->nodes[node].rotation);
    else
        out->q = IdentityQuaternion.q;
}

void get_animation_designer_node_rotXYZ_motion_ik_base(Vec4 *out, MotionIkBase *base)
{
    Vec4 quaternion;
    getNodeQuaternion(&quaternion, base);
    convert_from_quater_to_rotXYZ_motion_ik_base(out, &quaternion, base);
}

void convert_from_quater_to_rotXYZ_motion_ik_base(void *a, void *b, char **c)
{
    unsigned int *h = *(unsigned int **)(*c + 0x18);
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    char *p = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
    convert_from_quater_to_rotXYZ_direct_motion_ik_base(a, b, *(int *)(p + 0x14));
}

void convert_from_quater_to_rotXYZ_direct_motion_ik_base(void *rot, void *q, int mode)
{
    switch (mode) {
    case 0:
        GetEulerYXZFromQuaternion(rot, q);
        return;
    case 1:
        GetEulerZXYFromQuaternion(rot, q);
        return;
    default:
        __asm__ __volatile__("break 0");
    }
}

void convert_from_rotXYZ_to_quater_motion_ik_base(void *a, void *b, char **c)
{
    unsigned int *h = *(unsigned int **)(*c + 0x18);
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    char *p = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
    convert_from_rotXYZ_to_quater_direct_motion_ik_base(a, b, *(int *)(p + 0x14));
}

void convert_from_rotXYZ_to_quater_direct_motion_ik_base(float *q, float *r, int order)
{
    switch (order) {
    case 0:
        GetQuaternionByEulerYXZ(q, r[0], r[1], r[2]);
        break;
    case 1:
        GetQuaternionByEulerZXY(q, r[0], r[1], r[2]);
        break;
    default:
        __asm__ __volatile__("break 0");
        break;
    }
}
