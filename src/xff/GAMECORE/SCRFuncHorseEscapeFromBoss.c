typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern char gcGlobalVar[];
extern void *SCRGetFirstObj(void *);
extern void *getSCRDataCtrlWork(void *);
extern char *GetLayoutClass(void *);
extern void iosGetStabXZVector(float *, float *);
extern void setAttainmentPos(void *, float *);

static inline void vecSubW(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline void vecScale(float *dst, float *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}

static inline void vecAdd(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

void SCRFuncHorseEscapeFromBoss(void *obj, float dist)
{
    void *boss = SCRGetFirstObj(gcGlobalVar + 0x2B8);
    Vec4 v;

    if (boss != 0) {
        void *ctrl = getSCRDataCtrlWork(obj);
        char *lay = GetLayoutClass(obj);
        char *blay = GetLayoutClass(boss);

        vecSubW(v.f, *(float **)(lay + 0x134), *(float **)(blay + 0x134));
        iosGetStabXZVector(v.f, v.f);
        vecScale(v.f, v.f, dist);
        vecAdd(v.f, v.f, *(float **)(GetLayoutClass(obj) + 0x134));
        v.f[3] = 1.0f;
        setAttainmentPos(ctrl, v.f);
    }
}
