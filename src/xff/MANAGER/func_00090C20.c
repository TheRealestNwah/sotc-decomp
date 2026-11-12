#ifdef NONMATCHING
/* Parked: 2 diffs (cb reloaded into v0 instead of v1 for the jalr); flip/p1/p4 temps from the permuter, was 30; a second 40-min permuter run from the 2-diff base found nothing. */
extern void SetQuaternionByAxisRotateVWithNoRegularize(float *, short, float *);
extern void SetGeometryPointerNodePosState(void *, int, int, float *, void *);
extern float XUnitVector[4];

static inline void quatMul(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"
                         "lqc2 vf12, 0x0(%1)\n"
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
                         "sqc2 vf13, 0x0(%2)\n"
                         : : "r"(a), "r"(b), "r"(out) : "memory");
}

static void func_00090C20(void (*cb)(void *, void *, void *, void *, void *), void *p1, void *p2, void *p3,
                          void *p4, int node, int kind, float *rot, void *extra)
{
    char state[0x40] __attribute__((aligned(16)));
    float q[4] __attribute__((aligned(16)));
    void *v2;
    void *v1;
    float *pq = q;
    float flip[4] __attribute__((aligned(16)));

    v2 = flip;
    SetQuaternionByAxisRotateVWithNoRegularize(v2, -0x8000, XUnitVector);
    v2 = p1;
    quatMul(q, rot, flip);
    SetGeometryPointerNodePosState(state, node, kind, pq, extra);
    v1 = p4;
    cb(v2, p2, p3, v1, state);
}
#endif
