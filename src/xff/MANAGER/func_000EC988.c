typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct {
    float x, y, z, w;
} __attribute__((aligned(8))) Pos;
typedef struct {
    char pad[8];
    unsigned int node;
    float x, y, z;
    float rotY, rotX, rotZ;
    int global;
} NodeDef;
extern int *DldSysUndefSymbol;
extern int D_00139F78;
extern void *D_00139F80;
extern Vec4 D_00139F90;
extern Vec4 B_0015E440;
extern float IdentityQuaternion[];
extern char XUnitVector[], YUnitVector[], ZUnitVector[];
extern void CopyGeometryPointer(void *, void *);
extern void SetQuaternionByAxisRotateVWithNoRegularize(float *, short, void *);
extern void SetGeometryPointerNodePosState(void *, int, int, float *, Pos *);
extern void SetGeometryPointerNodePosStateGlobalRot(void *, int, int, float *, Pos *);

static inline void VU_QUAT_MUL(float *dst, float *a, float *b)
{
        __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"                          "lqc2 vf12, 0x0(%1)\n"                          "vmul.xyzw vf13, vf11, vf12\n"                          "vaddy.x vf13, vf13, vf13y\n"                          "vaddz.x vf13, vf13, vf13z\n"                          "vsubx.w vf13, vf13, vf13x\n"                          "vmulw.xyz vf14, vf12, vf11w\n"                          "vmulw.xyz vf15, vf11, vf12w\n"                          "vopmula.xyz ACC, vf12, vf11\n"                          "vopmsub.xyz vf16, vf11, vf12\n"                          "vadd.xyz vf13, vf14, vf15\n"                          "vadd.xyz vf13, vf13, vf16\n"                          "sqc2 vf13, 0x0(%2)\n"                          : : "r"(a), "r"(b), "r"(dst) : "memory");
}

/* Resolves a DLD symbol reference to its target address. */
static inline char *resolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

/* dst = src * (rotation by ang about axis). */
static inline void rotQuat(float *dst, float *src, int ang, char *axis)
{
    Vec4 r;

    SetQuaternionByAxisRotateVWithNoRegularize(r.f, ang, axis);
    VU_QUAT_MUL(dst, src, r.f);
}

static void func_000EC988(void *geo, NodeDef *def)
{
    Pos pos;
    Vec4 q;
    char *node;
    int idx;

    q.f[0] = -def->x;
    q.f[1] = def->y;
    q.f[2] = -def->z;
    q.f[3] = 1.0f;
    pos = *(Pos *)q.f;
    if (D_00139F80 == 0) {
        node = resolve(&def->node);
        if (node == 0) {
            SetGeometryPointerNodePosState(geo, D_00139F78, -2, IdentityQuaternion, &pos);
        } else {
            rotQuat(q.f, IdentityQuaternion, -(short)(int)(def->rotY * 32768.0f / 180.0f), YUnitVector);
            rotQuat(q.f, q.f, -(short)(int)(def->rotX * 32768.0f / 180.0f), XUnitVector);
            rotQuat(q.f, q.f, (int)(def->rotZ * 32768.0f / 180.0f), ZUnitVector);
            idx = *(int *)(node + 8);
            if (def->global != 0) {
                VU_QUAT_MUL(q.f, B_0015E440.f, q.f);
                SetGeometryPointerNodePosStateGlobalRot(geo, D_00139F78, idx, q.f, &pos);
            } else {
                VU_QUAT_MUL(q.f, D_00139F90.f, q.f);
                SetGeometryPointerNodePosState(geo, D_00139F78, idx, q.f, &pos);
            }
        }
    } else {
        CopyGeometryPointer(geo, D_00139F80);
    }
}
