#ifdef NONMATCHING /* 95 diffs: word count matches (144); saved-register numbering of the four args differs (declaration-order permutations of arg copies did nothing) */
extern int DldSysUndefSymbol;
extern int _BlendMotionDef;

static inline int *dldObj(unsigned int *h)
{
    unsigned int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return (t != 0 && t != (int *)DldSysUndefSymbol) ? t : 0;
}

typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern char XUnitVector[];
extern void GetMotionFloatFrame(void *, void *, void *, void *, float);
extern void GetMotionIntFrame(void *, void *, int, void *);
extern int GetMotionResourceRotAngle(int);
extern void SetQuaternionByAxisRotateVWithNoRegularize(float *, short, void *);
extern void MultiGlobalQuaternionToRootSkeleton(void *, void *, void *);

static inline void zero(s128 *v)
{
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(v) : "memory");
}

static inline void quatMul(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"
                         "lqc2 vf12, 0x0(%1)\n"
                         "vmul.xyzw vf13, vf11, vf12\n"
                         "vaddy.x vf13, vf13, vf13y\n"
                         "vaddz.x vf13, vf13, vf13z\n"
                         "vsubx.w vf13, vf13, vf13x\n"
                         "vmulw.xyz vf14, vf12, vf11w\n"
                         "vmulw.xyz vf15, vf11, vf12w\n"
                         "vopmula.xyz ACC, vf12, vf11\n"
                         "vopmsub.xyz vf16, vf11, vf12\n"
                         "vadd.xyz vf13, vf14, vf15\n"
                         "vadd.xyz vf13, vf13, vf16\n"
                         "sqc2 vf13, 0x0(%2)\n"
                         : : "r"(a), "r"(b), "r"(dst) : "memory");
}

void func_00048D48(void *a0, unsigned int *h1, char *c1, unsigned int *h2, char *c2, void *sel, void *t2)
{
    Vec4 buf[2];
    char *s0;
    int rot;
    unsigned int *h;

    if (h1) {
        if (dldObj(h1)[2] == (int)&_BlendMotionDef) {
            GetMotionFloatFrame(a0, h1, sel, t2, 0.0f);
        } else {
            GetMotionIntFrame(a0, h1, 0, t2);
        }
        s0 = *(char **)(c1 + 0x34);
        rot = GetMotionResourceRotAngle((int)s0);
        if (s0) {
            zero(&buf[0].q);
            SetQuaternionByAxisRotateVWithNoRegularize(buf[1].f, -(short)rot, XUnitVector);
            quatMul(buf[0].f, buf[0].f, buf[1].f);
            MultiGlobalQuaternionToRootSkeleton(a0, buf, sel);
        }
    } else {
        if (dldObj(h2)[2] == (int)&_BlendMotionDef) {
            GetMotionFloatFrame(a0, h2, sel, t2, 0.0f);
        } else {
            GetMotionIntFrame(a0, h2, 0, t2);
        }
        s0 = *(char **)(c2 + 0x34);
        rot = GetMotionResourceRotAngle((int)s0);
        if (s0) {
            zero(&buf[0].q);
            SetQuaternionByAxisRotateVWithNoRegularize(buf[1].f, -(short)rot, XUnitVector);
            quatMul(buf[0].f, buf[0].f, buf[1].f);
            MultiGlobalQuaternionToRootSkeleton(a0, buf, sel);
        }
    }
}
#endif
