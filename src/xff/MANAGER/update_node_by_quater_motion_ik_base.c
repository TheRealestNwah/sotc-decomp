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
extern void convert_from_rotXYZ_to_quater_motion_ik_base(float *, void *, MotWork **);
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
void update_node_by_rotXYZ_motion_ik_base(MotWork **pw, void *rot)
{
    float q[4] __attribute__((aligned(16)));

    convert_from_rotXYZ_to_quater_motion_ik_base(q, rot, pw);
    update_node_by_quater_motion_ik_base(pw, q);
}
