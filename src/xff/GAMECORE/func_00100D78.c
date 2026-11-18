typedef float Vec4[4] __attribute__((aligned(16)));
typedef unsigned int u_long128 __attribute__((mode(TI)));

extern char gcGlobalVar[];
extern void getTurnAndPitchFromDir(float *, float *, float *);
extern float calcAngleTime(float, float, float, float);
extern int ClipCollisionDirect(float *, void *, float *, void *);

static inline void vecSub(float *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vecAdd(float *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float vecLength(float *v)
{
    float len;

    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(len) : "r"(v) : "$2");
    return len;
}

static inline void vecNormalize(float *dst, float *src)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src) : "memory");
}

static inline float vecDot(float *a, float *b)
{
    float dot;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dot) : "r"(a), "r"(b) : "$2");
    return dot;
}

static inline void vecScale(float *dst, float *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}

static inline void applyMatrix(void *d, void *m, void *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%2)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(d), "r"(m), "r"(v) : "memory");
}

static void func_00100D78(u_long128 *out, u_long128 *pos, float *dir, char *obj)
{
    Vec4 d;
    Vec4 ofs;
    Vec4 h;
    Vec4 p;
    Vec4 q;
    Vec4 w;
    char col[0x50] __attribute__((aligned(16)));
    float turn0, pitch0, turn1, pitch1;
    char *wk;
    char *base;
    float len, total, dist, t, a, b, f, ta, tb;

    wk = *(char **)(obj + 0xCC);
    vecSub(d, pos, obj + 0x120);
    len = vecLength(d);
    total = len / *(float *)(wk + 0x224);
    vecNormalize(d, d);
    a = vecDot(d, dir);
    vecAdd(h, d, dir);
    vecNormalize(h, h);
    b = vecDot(h, dir);
    dist = len * a / b;
    vecScale(ofs, h, -dist);
    *out = *pos;
    dist = __builtin_fabsf(dist);
    base = obj + 0x120;
    f = 0.19999999f;
    getTurnAndPitchFromDir(dir, &turn0, &pitch0);
    do {
        t = dist * f / *(float *)(wk + 0x224);
        if (t < 2.0f || total - t < 2.0f)
            continue;
        vecScale(p, ofs, f);
        vecAdd(p, p, pos);
        vecSub(q, p, base);
        vecNormalize(q, q);
        getTurnAndPitchFromDir(q, &turn1, &pitch1);
        ta = calcAngleTime(turn1 - turn0, *(float *)(obj + 0x148), *(float *)(*(char **)(obj + 0xCC) + 0x9C),
                          *(float *)(*(char **)(obj + 0xCC) + 0xA8));
        tb = calcAngleTime(pitch1 - pitch0, *(float *)(obj + 0x14C), *(float *)(*(char **)(obj + 0xCC) + 0x98),
                          *(float *)(*(char **)(obj + 0xCC) + 0xA8));
        if (ta < t && tb < t) {
            p[3] = 1.0f;
            applyMatrix(w, obj + 0x60, p);
            if (ClipCollisionDirect(col, *(void **)(*(char **)(obj + 0x18) + 0x134), w, gcGlobalVar + 0x238) == 0) {
                *out = *(u_long128 *)p;
                return;
            }
        }
    } while ((f += 0.0999999940395355224609375f) <= 0.79999995231628418f);
}
