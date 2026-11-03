#ifdef NONMATCHING /* 25 diffs; the permuter got to 500 from 555 without a match */
typedef struct {
    float v[4];
} Vec4 __attribute__((aligned(16)));

typedef struct {
    char pad0[8];
    void *data;
} MotionTrack;

typedef struct {
    char pad0[4];
    short frames;
    char pad6[0xA];
    MotionTrack *tracks;
} Motion;

extern void func_0003A168(void *, void *, float);
extern void func_0003A4A8(Vec4 *, void *, void *, int, float, float);

static inline void addXYZ(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void scaleXYZ(Vec4 *out, Vec4 *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}

void GetMotionNS_RootShiftInfo(void *work, Vec4 *out, Motion *m0, Motion *m1, int node,
                               float t0, float r0, float t1, float r1, float scale)
{
    Vec4 buf;
    Vec4 tmp;
    MotionTrack *a = &m0->tracks[node];
    MotionTrack *b = &m1->tracks[node];
    void *d0 = a->data;
    void *d1 = b->data;
    int n0 = m0->frames;
    int n1 = m1->frames;

    func_0003A168(work, d0, t0);
    func_0003A4A8(out, work, d0, n0, t0, r0);
    func_0003A168(&buf, d1, t1);
    func_0003A4A8(&tmp, &buf, d1, n1, t1, r1);
    addXYZ(out, out, &tmp);
    scaleXYZ(out, out, scale);
    out->v[3] = 0;
}
#endif
