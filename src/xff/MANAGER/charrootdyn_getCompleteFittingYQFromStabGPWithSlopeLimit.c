/* Parked: 7 diffs, same size (100 words). Calling GetGeometryPointerSurfacePlane before the barrier (a permuter hint) fixed the s1/s2 swap. The YQ-from-Y-dir tail is the inlined body of charrootdyn_getCompleteFittingYQFromYDir; a clobber-free asm after GetGeometryPointerPosition makes gcc recompute sp+0x10 for getAverageNormal like the Original. Remaining: the argument setup order for getAverageNormal (the Original sets a2 and a0 before the float moves). */
#ifdef NONMATCHING
extern void GetDifferencialQuaternionWithNoRegularize(float *, float *, float *, float *);

static inline void quatAxisY(float *out, float *q)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf4, 0x0(%1)\n"
        "vmul.xyzw vf5, vf4, vf4\n"
        "vmr32.xyzw vf6, vf4\n"
        "vmul.xyzw vf7, vf6, vf4\n"
        "vaddy.z vf6, vf0, vf7y\n"
        "vsubw.z vf6, vf6, vf7w\n"
        "vsubx.y vf6, vf0, vf5x\n"
        "vsubz.y vf6, vf6, vf5z\n"
        "vaddz.x vf6, vf7, vf7z\n"
        "vsub.w vf6, vf0, vf0\n"
        "vadd.w vf5, vf0, vf0\n"
        "vmulw.xyz vf6, vf6, vf5w\n"
        "vaddw.y vf6, vf6, vf0w\n"
        "sqc2 vf6, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(out), "r"(q) : "memory");
}

static inline void quatAxisZ(float *out, float *q)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf4, 0x0(%1)\n"
        "vmul.xyzw vf5, vf4, vf4\n"
        "vmr32.xyzw vf6, vf4\n"
        "vmul.xyzw vf7, vf6, vf4\n"
        "vmr32.xyzw vf6, vf6\n"
        "vmul.xyzw vf8, vf6, vf4\n"
        "vsubx.z vf6, vf0, vf5x\n"
        "vsuby.z vf6, vf6, vf5y\n"
        "vaddw.y vf6, vf7, vf7w\n"
        "vsuby.x vf6, vf8, vf8y\n"
        "vsub.w vf6, vf0, vf0\n"
        "vadd.w vf5, vf0, vf0\n"
        "vmulw.xyz vf6, vf6, vf5w\n"
        "vaddw.z vf6, vf6, vf0w\n"
        "sqc2 vf6, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(out), "r"(q) : "memory");
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

static inline void quatNormalize(float *out, float *in)
{
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)\n"
                         "vmul.xyzw vf15, vf14, vf14\n"
                         "vaddy.x vf15, vf15, vf15y\n"
                         "vaddz.x vf15, vf15, vf15z\n"
                         "vaddw.x vf15, vf15, vf15w\n"
                         "vrsqrt Q, vf0w, vf15x\n"
                         "vwaitq\n"
                         "vmulq.xyzw vf15, vf14, Q\n"
                         "sqc2 vf15, 0x0(%0)\n"
                         : : "r"(out), "r"(in) : "memory");
}

typedef float Vec4[4] __attribute__((aligned(16)));
extern void GetGeometryPointerPosition(void *, void *);
extern void *GetGeometryPointerSurfacePlane(void *);
extern int getAverageNormal(void *, float, void *, void *, void *, float, float, int, int, void *);

static inline void yqFromYDir(float *out, float *dir, float *q)
{
    Vec4 y;
    Vec4 z;
    Vec4 d;

    quatAxisY(y, q);
    quatAxisZ(z, q);
    GetDifferencialQuaternionWithNoRegularize(d, dir, y, z);
    quatMul(out, d, q);
    quatNormalize(out, out);
}

int charrootdyn_getCompleteFittingYQFromStabGPWithSlopeLimit(float *out, void *gp, int p2, float *q, int p4, float lim0, float lim1)
{
    struct { Vec4 dir; Vec4 pos; Vec4 n[4]; } L;
    int r;
    float *plane;

    GetGeometryPointerPosition(L.pos, gp);
    plane = GetGeometryPointerSurfacePlane(gp);
    __asm__ __volatile__("" : : );
    r = getAverageNormal(L.dir, lim0, L.n[0], q, L.pos, lim0, lim1, p2, p4, plane);
    yqFromYDir(out, L.dir, q);
    return r;
}
#endif
