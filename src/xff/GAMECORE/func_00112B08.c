typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern void func_00113118(char *p, float *q);
extern void func_00111218(Vec4 *pos, Vec4 *dir, int n, char *p);

static inline void vecSub(void *d, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void vecAdd(void *d, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void vecNormalize(void *d, void *s)
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
                         : : "r"(d), "r"(s) : "memory");
}

static inline void vecScale(void *d, void *s, float k)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(s), "r"(k) : "memory");
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

static inline float vecDot(void *a, void *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

static void func_00112B08(char *p, Vec4 *target)
{
    Vec4 tmp;
    Vec4 pos;
    Vec4 dir;
    Vec4 loc;
    Vec4 n1;
    Vec4 n2;
    Vec4 *pp = &pos;
    char *c = *(char **)(p + 0xCC);
    int type = *(int *)(c + 0xBC);

    if (type == 3) {
        vecSub(&dir, target, p + 0x110);
        vecNormalize(&dir, &dir);
        vecScale(&dir, &dir, 5.0f);
        vecAdd(pp, &dir, p + 0x110);
        pp->f[3] = 1.0f;
        applyMatrix(&loc, p + 0x60, pp);
        func_00113118(p, loc.f);
        applyMatrix(pp, p + 0x20, &loc);
    } else if (type == 5) {
        vecSub(&dir, target, p + 0x110);
        dir.f[1] = 0.0f;
        vecNormalize(&dir, &dir);
        vecScale(&dir, &dir, 5.0f);
        vecAdd(pp, &dir, p + 0x110);
        pp->f[3] = 1.0f;
        applyMatrix(&loc, p + 0x60, pp);
        loc.f[1] = *(float *)(c + 0xC0);
        applyMatrix(pp, p + 0x20, &loc);
    } else {
        pos.q = target->q;
    }
    vecSub(&n1, p + 0x100, target);
    vecNormalize(&n1, &n1);
    vecSub(&n2, target, p + 0x110);
    vecNormalize(&n2, &n2);
    if (vecDot(&n1, p + 0xD0) < vecDot(&n2, p + 0xD0))
        tmp.q = n2.q;
    else
        tmp.q = ((Vec4 *)(p + 0xD0))->q;
    func_00111218(pp, &tmp, 0, p);
}
