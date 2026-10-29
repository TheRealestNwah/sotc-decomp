typedef float Vec4[4] __attribute__((aligned(16)));
extern void GetLayoutClassWindGeometry(void *);
extern void GetPlaneFittingVector(void *, void *, void *);
static inline void quaternionY(void *out, void *q)
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
static inline float length3(void *p)
{
    float result;
    __asm__ __volatile__(
        "lqc2 vf7, 0(%1)\n" "vmul.xyz vf7, vf7, vf7\n"
        "vmulax.w ACC, vf0, vf7x\n" "vmadday.w ACC, vf0, vf7y\n"
        "vmaddz.w vf7, vf0, vf7z\n" "vsqrt Q, vf7w\n" "vwaitq\n"
        "cfc2 $2, $vi22\n" "mtc1 $2, %0\n"
        : "=f"(result) : "r"(p) : "$2");
    return result;
}
static inline float squareLength3(void *p)
{
    float result;
    __asm__ __volatile__(
        "lqc2 vf7, 0(%1)\n" "vmul.xyz vf7, vf7, vf7\n"
        "vaddy.x vf7, vf7, vf7y\n" "vaddz.x vf7, vf7, vf7z\n"
        "qmfc2 $2, vf7\n" "mtc1 $2, %0\n"
        : "=f"(result) : "r"(p) : "$2");
    return result;
}
void SetCharacterClassWindDynamics(char *layout)
{
    Vec4 y, first, second;
    GetLayoutClassWindGeometry(layout);
    quaternionY(y, *(void **)(layout + 0x13C));
    GetPlaneFittingVector(first, y, *(char **)(layout + 0x19C) + 0x60);
    *(float *)(layout + 0x514) = length3(first);
    GetPlaneFittingVector(second, y, *(char **)(layout + 0x19C) + 0x70);
    *(float *)(layout + 0x518) = squareLength3(second);
}
