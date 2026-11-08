typedef int s128 __attribute__((mode(TI)));
typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4;

extern char gcGlobalVar[];
extern char *GetCharacterClass(void *);
extern char *GetLayoutClass(void *);
extern int ClipCollisionDirectCallBack(void *, void *, void *, void *, int, int, int, void *, int);
extern int func_001205B0(void *);

static inline void vecScale(void *out, void *v, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%2)\n"
                         : : "r"(v), "r"(s), "r"(out) : "memory");
}

#ifdef NONMATCHING
/* Parked: 18 words differ (callee-saved register assignment of the four stack-vector pointers; two prologue call orders). */
int SCRConditionAtkChackThreeRayParallel(void *obj, float a, float b, float c)
{
    struct { Vec4 v10; char buf[0x50]; Vec4 v70; Vec4 v80; Vec4 v90; Vec4 vA0; Vec4 vB0; Vec4 vC0; Vec4 vD0; Vec4 vE0; } L;
    int i;
    float fa;
    float fb;

    if (c <= 0.0f)
        c = 0.1f;
    fa = a * c;
    fb = b * c;
    *(s128 *)&L.v70 = **(s128 **)(GetLayoutClass(obj) + 0x134);
    *(s128 *)&L.v10 = *(s128 *)(GetCharacterClass(obj) + 0x470);
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
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
                         : : "r"(&L.v80), "r"(GetCharacterClass(obj) + 0x470) : "memory");
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vmr32.xyzw vf6, vf6\n"
                         "vmul.xyzw vf8, vf6, vf4\n"
                         "vsubz.x vf6, vf7, vf7z\n"
                         "vaddx.y vf6, vf0, vf6x\n"
                         "vsuby.x vf6, vf0, vf5y\n"
                         "vsubz.x vf6, vf6, vf5z\n"
                         "vaddw.z vf6, vf8, vf8w\n"
                         "vsub.w vf6, vf6, vf6\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.x vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(&L.vC0), "r"(&L.v10) : "memory");
    vecScale(&L.vE0, &L.vC0, fb);
    *(s128 *)&L.v90 = *(s128 *)&L.v70;
    for (i = 0; i < 3;) {
        if (i == 1) {
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\nlqc2 vf6, 0x0(%1)\nvadd.xyz vf5, vf5, vf6\nsqc2 vf5, 0x0(%2)\n"
                                 : : "r"(&L.v70), "r"(&L.vE0), "r"(&L.vD0) : "memory");
            *(s128 *)&L.v90 = *(s128 *)&L.vD0;
        }
        if (i == 2) {
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\nlqc2 vf6, 0x0(%1)\nvsub.xyz vf5, vf5, vf6\nsqc2 vf5, 0x0(%2)\n"
                                 : : "r"(&L.v70), "r"(&L.vE0), "r"(&L.vD0) : "memory");
            *(s128 *)&L.v90 = *(s128 *)&L.vD0;
        }
        vecScale(&L.vB0, &L.v80, fa);
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\nlqc2 vf6, 0x0(%1)\nvadd.xyz vf5, vf5, vf6\nsqc2 vf5, 0x0(%2)\n"
                             : : "r"(&L.v90), "r"(&L.vB0), "r"(&L.vA0) : "memory");
        i++;
        if (ClipCollisionDirectCallBack(L.buf, &L.v90, &L.vA0, gcGlobalVar + 0x238, 0, 0, 0, func_001205B0, 0) != 0)
            return 0;
    }
    return 1;
}
#else
int SCRConditionAtkChackThreeRayParallel(void *obj, float a, float b, float c);
#endif
