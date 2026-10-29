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
extern int *DldSysUndefSymbol;
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

extern void convert_from_quater_to_rotXYZ_motion_ik_base(Vec4 *, Vec4 *, MotionIkBase *);
void get_animation_designer_node_rotXYZ_motion_ik_base(Vec4 *out, MotionIkBase *base)
{
    Vec4 quaternion;
    getNodeQuaternion(&quaternion, base);
    convert_from_quater_to_rotXYZ_motion_ik_base(out, &quaternion, base);
}
