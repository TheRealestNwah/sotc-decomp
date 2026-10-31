typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    Vec4 pos;
    Vec4 plane;
    Vec4 normal;
} ClipHit;

typedef struct {
    int hit;
    float distSq;
    float slope;
    char padC[4];
    Vec4 pos;
} NipPlaneStatus;

typedef struct {
    char pad0[0xE20];
    char clip[0xE34 - 0xE20];
    float nipLength;
} RootDynamics;

extern Vec4 *GetGeometryPointerSurfacePlane(void *);
extern void GetGeometryPointerPosition(Vec4 *, void *);
extern void iosGetStabXZVector(Vec4 *, Vec4 *);
extern int ClipCollisionFinderWithKeepSlopeLimit(ClipHit *, Vec4 *, Vec4 *, void *, float, int);
extern float GetPlaneSlopeDegree(Vec4 *);

static inline void vecScale(float *out, float *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}

static inline void vecAdd(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float vecDistSq(float *a, float *b)
{
    float d;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

int charrootdyn_getNipPlaneStatus(NipPlaneStatus *out, RootDynamics *root, void *geometry)
{
    Vec4 stab;
    Vec4 offset;
    Vec4 pos;
    Vec4 start;
    Vec4 end;
    ClipHit hit;
    Vec4 *plane;
    float y;
    int ret;

    plane = GetGeometryPointerSurfacePlane(geometry);
    ret = 0;
    y = plane->f[1];
    if (y < 0.0f ? y < -0.999f : 0.999f < y)
        return ret;
    iosGetStabXZVector(&stab, plane);
    vecScale(stab.f, stab.f, root->nipLength);
    vecScale(offset.f, plane->f, 0.01f);
    GetGeometryPointerPosition(&pos, geometry);
    vecAdd(start.f, pos.f, offset.f);
    vecAdd(end.f, start.f, stab.f);
    ret = ClipCollisionFinderWithKeepSlopeLimit(&hit, &start, &end, root->clip, 0.0f, 0);
    if (ret == 0)
        return ret;
    out->hit = 1;
    out->distSq = vecDistSq(pos.f, hit.pos.f);
    out->slope = GetPlaneSlopeDegree(&hit.plane);
    {
        Vec4 *p = &hit.pos;

        out->pos.q = p->q;
    }
    return 1;
}
