typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
extern s128 YUnitVector;
extern s128 ZUnitVector;
extern float iosGetACosfExact(float);
extern void GetQuaternionByAxisDirZY(void *, float *, void *);

static inline float getPlaneAngle(float *normal)
{
    float y = normal[1];

    if (y >= 1.0f)
        return 0.0f;
    if (y <= -1.0f)
        return 180.0f;
    return iosGetACosfExact(y) * 57.29578f;
}

static inline void outerProduct(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void normalize(void *out, void *in)
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
                         : : "r"(out), "r"(in) : "memory");
}

void GetPlaneTopDir(s128 *out, float *normal)
{
    Vec4 side;

    if (getPlaneAngle(normal) != 0.0f) {
        outerProduct(side.f, normal, &YUnitVector);
        outerProduct(out, side.f, normal);
        normalize(out, out);
    } else {
        *out = ZUnitVector;
    }
}

void GetPlaneFittingVector(void *dst, void *p, void *n)
{
    float d;

    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni %0, vf6\n"
                         ".set reorder\n"
                         : "=r"(d) : "r"(p), "r"(n));
    d = -d;
    __asm__ __volatile__(".set noreorder\n"
                         "mfc1 $8, %3\n"
                         "qmtc2.ni $8, vf30\n"
                         "lqc2 vf29, 0x0(%1)\n"
                         "vmulx.xyzw vf31, vf29, vf30x\n"
                         "lqc2 vf29, 0x0(%2)\n"
                         "vmove.xyzw vf30, vf31\n"
                         "vmove.xyzw vf31, vf29\n"
                         "vadd.xyz vf31, vf29, vf30\n"
                         "sqc2 vf31, 0x0(%0)\n"
                         ".set reorder\n"
                         : : "r"(dst), "r"(p), "r"(n), "f"(d) : "$8", "memory");
}

void GetPlaneZTopYPlaneCoordQuaternion(void *q, void *plane)
{
    float dir[4] __attribute__((aligned(16)));
    GetPlaneTopDir(dir, plane);
    GetQuaternionByAxisDirZY(q, dir, plane);
}
