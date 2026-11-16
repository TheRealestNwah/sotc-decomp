#ifdef NONMATCHING /* 56 diffs: word count matches (129); the ZeroVector hi/lo pair is hoisted above the 0x124 load (target keeps it after the branch); explicit %hi/%lo asm did not help */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern float ZeroVector[4];
extern float GetGeometryPointerSurfaceSlopeDegree(void *, float *);
extern float *GetGeometryPointerSurfacePlane(void *);
extern void GetPlaneFittingVector(void *, void *, void *);
extern float iosFastPowf(float, float);

static inline void zero(s128 *v)
{
    __asm__ __volatile__("sq $0, 0(%0)" : : "r"(v) : "memory");
}

static inline void scaleXYZ(float *v, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v), "r"(s) : "memory");
}

static inline void scaleTo(float *dst, float *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "qmtc2.ni %2, vf6
"
                         "vmulx.xyz vf5, vf5, vf6x
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}

static inline void addXYZ(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

int charrootdyn_addSlideElement(float *vel, float *out, float *src, float *pos, char *obj,
                                float a, float b, float pad, float dt)
{
    Vec4 buf[4];
    float slope = 0.0f;
    float f1;
    float lim;
    float t;
    float len2;
    float *plane;
    char *g = obj + 0xC0;
    float *zv;

    *(s128 *)vel = *(s128 *)src;
    obj[0x10A1] = 0;
    __asm__ __volatile__("" ::: "memory");
    if (*(int *)(obj + 0x124) != 0) {
        zv = ZeroVector;
        slope = GetGeometryPointerSurfaceSlopeDegree(g, zv);
        plane = GetGeometryPointerSurfacePlane(g);
        zero(&buf[2].q);
        zero(&buf[1].q);
        zero(&buf[0].q);
        if (obj[0xC96] != 0) {
            buf[2].q = *(s128 *)zv;
            buf[2].f[1] = -14.699999f;
            GetPlaneFittingVector(buf[1].f, plane, buf[2].f);
            scaleXYZ(buf[1].f, dt);
            addXYZ(buf[0].f, buf[0].f, buf[1].f);
            obj[0xC96] = 0;
            obj[0x10A1] = 1;
        }
        scaleTo(buf[3].f, vel, dt);
        addXYZ(out, pos, buf[3].f);
        addXYZ(vel, vel, buf[0].f);
    }
    lim = 90.0f;
    f1 = lim;
    if (!(lim < slope))
        f1 = slope;
    t = f1 * 0.011111111f;
    t = t * t;
    scaleXYZ(vel, iosFastPowf((b - a) * t + a, dt * 30.0f));
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(len2) : "r"(vel) : "$2", "memory");
    if (len2 > 0.0001f)
        return 1;
    *(s128 *)vel = *(s128 *)ZeroVector;
    return 0;
}
#endif
