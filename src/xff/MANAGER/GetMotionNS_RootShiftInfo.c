#ifdef NONMATCHING /* 10 diffs: d1, n0 and n1 get $s4, $s5 and $s3 where the Original has $s3, $s4 and $s5, and the a3/f13 argument moves are scheduled in the other order */
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

static inline void rootShift(Vec4 *dst, void *w, void *d, int n, float t, float r)
{
    func_0003A168(w, d, t);
    func_0003A4A8(dst, w, d, n, t, r);
}

void GetMotionNS_RootShiftInfo(void *work, Vec4 *out0, Motion *m0, Motion *m1, int node,
                               float t0, float r0, float t1, float r1, float scale)
{
    Vec4 *out = out0;
    Vec4 buf;
    Vec4 tmp;
    Vec4 *o2, *o3;
    MotionTrack *a = &m0->tracks[node];
    MotionTrack *b = &m1->tracks[node];
    void *d0 = a->data;
    void *d1 = b->data;
    int n0 = m0->frames;
    int n1 = m1->frames;

    rootShift(out, work, d0, n0, t0, r0);
    rootShift(&tmp, &buf, d1, n1, t1, r1);
    o2 = out;
    addXYZ(o2, o2, &tmp);
    o3 = o2;
    scaleXYZ(o3, out, scale);
    o3->v[3] = 0.0f;
}
#endif
