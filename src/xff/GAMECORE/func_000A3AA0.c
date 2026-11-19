typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern Vec4 ZUnitVector, YUnitVector;
extern int isysGetThisSubThread(void);
extern char *GetLayoutClass(int);
extern int Kite_CmpPathPoint(void *, void *);
extern void GetDifferencialQuaternionWithNoRegularize(float *, float *, void *, void *);
extern float AI_GetInterRatio(float, float, float, float, float);

static inline float distXYZ(void *a, void *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

static inline void subV(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float lenXYZ(void *a)
{
    float r;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a) : "$2");
    return r;
}

static inline void normalizeXYZ(void *output, void *input)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf5, 0x0(%1)\n"
        "vmul.xyz vf7, vf5, vf5\n"
        "vmulax.w ACC, vf0, vf7x\n"
        "vmadday.w ACC, vf0, vf7y\n"
        "vmaddz.w vf7, vf0, vf7z\n"
        "vrsqrt Q, vf0w, vf7w\n"
        "vwaitq\n"
        "vmulq.xyz vf5, vf5, Q\n"
        "sqc2 vf5, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(output), "r"(input) : "memory");
}

static inline void quatRotateVector(Vec4 *out, float *quat, Vec4 *vec)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"
                         "vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%1)\n"
                         "vmr32.w vf14, vf0\n"
                         "vmr32.w vf15, vf0\n"
                         "vmr32.w vf16, vf0\n"
                         "vopmula.xyz ACC, vf11, vf12\n"
                         "vmadd.xyz vf11, vf0, vf0\n"
                         "vmadd.xyz vf10, vf11, vf12\n"
                         "vmul.xyz vf13, vf11, vf10\n"
                         "vopmula.xyz ACC, vf11, vf10\n"
                         "vmaddw.xyz vf15, vf10, vf11w\n"
                         "vmsubw.xyz vf16, vf10, vf11w\n"
                         "vopmula.xyz ACC, vf13, vf12\n"
                         "vmadd.xyz vf17, vf13, vf12\n"
                         "vopmula.xyz ACC, vf15, vf12\n"
                         "vmadd.xyz vf15, vf0, vf0\n"
                         "vsub.xyz vf14, vf12, vf17\n"
                         "vmove.yz vf17, vf14\n"
                         "vmove.y vf14, vf16\n"
                         "vmove.y vf16, vf15\n"
                         "vmove.y vf15, vf17\n"
                         "vmove.z vf14, vf15\n"
                         "vmove.z vf15, vf16\n"
                         "vmove.z vf16, vf17\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf0, vf8w\n"
                         : : "r"(vec), "r"(quat));
    __asm__ __volatile__("sqc2 vf10, 0x0(%0)\n" : : "r"(out) : "memory");
}


/* Parked: 5 words differ (register allocation around the quaternion temporaries); permuter found no plausible change */
#ifdef NONMATCHING
static float func_000A3AA0(char *w, float max)
{
    Vec4 d, q, a, b;
    char *me, *other;
    int sign;
    float dist, r;

    if (*(int *)(w + 0x38) != 0 || *(int *)(w + 0x40) != 0 || *(int *)(w + 0x28) == 0
        || *(int *)(w + 0x2C) == 0)
        return 0.0f;
    me = GetLayoutClass(isysGetThisSubThread());
    other = GetLayoutClass(*(int *)(w + 0x28));
    if (Kite_CmpPathPoint(w + 0x600, *(char **)(w + 0x2C) + 0x640) != 0) {
        dist = distXYZ(*(void **)(me + 0x134), *(void **)(other + 0x134));
        sign = -1;
    } else if (Kite_CmpPathPoint(w + 0x600, *(char **)(w + 0x2C) + 0x680) != 0) {
        dist = distXYZ(*(void **)(me + 0x134), *(void **)(other + 0x134));
        sign = 1;
    } else {
        subV(&d, w + 0x600, w + 0x680);
        if (lenXYZ(&d) == 0.0f)
            return 0.0f;
        subV(&a, *(void **)(me + 0x134), w + 0x680);
        subV(&b, *(void **)(other + 0x134), w + 0x680);
        normalizeXYZ(&d, &d);
        GetDifferencialQuaternionWithNoRegularize(q.f, ZUnitVector.f, &d, &YUnitVector);
        quatRotateVector(&a, q.f, &a);
        quatRotateVector(&b, q.f, &b);
        dist = b.f[2] - a.f[2];
        sign = dist < 0.0f ? -1 : 1;
    }
    r = AI_GetInterRatio(dist < 0.0f ? -dist : dist, *(float *)(*(char **)(w + 0x20) + 0x14),
                         *(float *)(*(char **)(w + 0x20) + 0x14) * 2.0f, 0.0f, max);
    if (max < r)
        r = max;
    if (r < 0.0f)
        r = 0.0f;
    return r * (float)sign;
}
#endif
