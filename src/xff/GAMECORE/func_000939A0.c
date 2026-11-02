typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern char *GetSCRCharaAIWorkPtr(void *);
extern void *memset(void *, int, unsigned int);
extern char *SkelFocusDef_BOSS_OPT_ATTACK;
extern void GetMotionNodeQuaternionPos(Vec4 *, Vec4 *, void *, int, int);
extern char *GetLayoutClass(void *);
extern float iosGetRandom(void);
extern void iosRotMatrixY(Vec4 *, float);
extern void func_00094340(void *, Vec4 *, char *);

static inline void vecSub4(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
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

static inline void vecAdd(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline void matApply(float *out, float *m, float *v)
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
                         : : "r"(out), "r"(m), "r"(v) : "memory");
}

static void func_000939A0(void *obj)
{
    char *ai = GetSCRCharaAIWorkPtr(obj);
    Vec4 ofs;
    Vec4 pos;
    Vec4 quat;
    Vec4 rot[4];
    Vec4 npos;
    Vec4 *p;
    char *lay;

    memset(&ofs, 0, 0x10);
    ofs.f[3] = 1.0f;
    GetMotionNodeQuaternionPos(&npos, &quat, obj, *(int *)(SkelFocusDef_BOSS_OPT_ATTACK + 8), 1);
    lay = GetLayoutClass(obj);
    p = &pos;
    vecSub4(p->f, *(float **)(lay + 0x134), *(float **)(*(char **)(ai + 0x408C) + 0x134));
    p->f[1] = 0.0f;
    vecNormalize(p->f);
    vecScale(p->f, p->f, 0.1f);
    vecAdd(p->f, p->f, *(float **)(*(char **)(ai + 0x408C) + 0x134));
    ofs.f[2] = iosGetRandom() * 0.03f;
    iosRotMatrixY(rot, iosGetRandom() * 3.14159265f * 2.0f);
    matApply(ofs.f, rot[0].f, ofs.f);
    vecAdd(ofs.f, ofs.f, p->f);
    func_00094340(obj, &ofs, SkelFocusDef_BOSS_OPT_ATTACK);
}
