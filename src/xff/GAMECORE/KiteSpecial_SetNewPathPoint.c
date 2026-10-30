typedef float Vec4[4] __attribute__((aligned(16)));
typedef unsigned int u_long128 __attribute__((mode(TI)));
typedef union { u_long128 q; float f[4]; } VecQ;

typedef struct {
    Vec4 center;
    float radius;
    float height;
} KiteArea;

extern void func_000ACDF0(float *, void *, char *);
extern float iosGetRandom(void);
extern float AI_GetInterRatio(float, float, float, float, float);

static inline void vecSubXYZ(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline void vecAddXYZ(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline float vecLength(float *v)
{
    float d;

    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(v) : "$2", "memory");
    return d;
}

static inline float vecDist(float *a, float *b)
{
    float d;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static inline void vecNormalize(float *v)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v) : "memory");
}

static inline void vecScale(float *dst, float *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}

void KiteSpecial_SetNewPathPoint(float *pt, int unused, char *kite, float *target)
{
    KiteArea *area = (KiteArea *)(kite + 0x100);
    Vec4 d;
    Vec4 dir;
    Vec4 ofs;
    float dy;
    float h;

    func_000ACDF0(pt, kite + 0x1F0, kite);
    vecSubXYZ(d, pt, area->center);
    dy = d[1];
    d[1] = 0;
    ((VecQ *)dir)->q = ((VecQ *)d)->q;
    {
        float len = vecLength(d);
        float r = area->radius;

        if (r < len) {
            float lim;
            float t;

            lim = (d[1] < r - 50.0f) ? r - 50.0f : r * 0.5f;
            t = AI_GetInterRatio(iosGetRandom(), 0.0f, 1.0f, lim, r);
            vecNormalize(dir);
            vecScale(ofs, dir, t);
            pt[0] = area->center[0] + ofs[0];
            pt[2] = area->center[2] + ofs[2];
        }
    }
    h = -area->height;
    if (dy < h) {
        ofs[1] = h;
        pt[1] = area->center[1] + ofs[1];
    }
    if (30.0f < vecDist(target, pt)) {
        vecSubXYZ(ofs, pt, target);
        vecNormalize(ofs);
        vecScale(ofs, ofs, 30.0f);
        vecAddXYZ(pt, target, ofs);
    }
}
