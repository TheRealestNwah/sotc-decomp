#ifdef NONMATCHING
/* a/out land in s1/s0 swapped (same issue as GetMotionNS_RootInfo), which also reorders the float saves. */
typedef struct { int pad[2]; void *data; } MotionNode;
typedef struct { int pad; short num; short pad6; int pad8[2]; MotionNode *nodes; } Motion;
extern void func_0003A168(void *, void *);
extern void func_0003A4A8(float *, void *, void *, float, float, int);

void GetMotionNS_RootShiftInfo(void *a, float *out, Motion *m1, Motion *m2, int idx,
                               float t0a, float t1a, float t0b, float t1b, float scale)
{
    float tmpa[4] __attribute__((aligned(16)));
    float tmpo[4] __attribute__((aligned(16)));
    MotionNode *nd1 = &m1->nodes[idx];
    MotionNode *nd2 = &m2->nodes[idx];
    int n1 = m1->num;
    void *d1 = nd1->data;
    void *d2 = nd2->data;
    int n2 = m2->num;

    func_0003A168(a, d1);
    func_0003A4A8(out, a, d1, t0a, t1a, n1);
    func_0003A168(tmpa, d2);
    func_0003A4A8(tmpo, tmpa, d2, t0b, t1b, n2);
    __asm__ __volatile__(
        "lqc2 vf5, 0x0(%0)\n"
        "lqc2 vf6, 0x0(%1)\n"
        "vadd.xyz vf5, vf5, vf6\n"
        "sqc2 vf5, 0x0(%0)\n"
        : : "r"(out), "r"(tmpo) : "memory");
    __asm__ __volatile__(
        "lqc2 vf5, 0x0(%0)\n"
        "qmtc2.ni %1, vf6\n"
        "vmulx.xyz vf5, vf5, vf6x\n"
        "sqc2 vf5, 0x0(%0)\n"
        : : "r"(out), "r"(scale) : "memory");
    out[3] = 0.0f;
}
#endif
