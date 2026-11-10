typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern int AI_CheckHorseParent(int);
extern int AI_CheckNormZero(void *);
extern float AI_GetInterRatioOutCut(float, float, float, float, float);
extern void func_000B0160(void *, void *, int, float);

#ifdef NONMATCHING /* 62 diffs: the original hoists 1.0f/3.0f into $f20/$f13 before the horse-parent branch and keeps 1.0f in callee-saved $f20 */
static void func_000B0D08(char *c)
{
    Vec4 v;
    float ratio;
    float f12;
    float one = 1.0f;

    *(int *)(c + 0x1A0) = 0x28;
    v.q = *(s128 *)(c + 0xC0);
    v.f[1] = 0.0f;
    if (AI_CheckHorseParent(*(int *)(c + 0x44)) != 0) {
        ratio = AI_GetInterRatioOutCut(*(float *)(c + 0x140), 0.0f, one, one, 1.0999999047f);
    } else {
        ratio = AI_GetInterRatioOutCut(*(float *)(c + 0x140), 3.0f, 10.0f, one, 1.0999999047f);
    }
    if (*(float *)(c + 0x200) < ratio) {
        *(float *)(c + 0x200) = ratio;
    }
    f12 = 0.0f;
    if (AI_CheckNormZero(&v) != 0) {
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "vmul.xyz vf7, vf5, vf5\n"
                             "vmulax.w ACC, vf0, vf7x\n"
                             "vmadday.w ACC, vf0, vf7y\n"
                             "vmaddz.w vf7, vf0, vf7z\n"
                             "vrsqrt Q, vf0w, vf7w\n"
                             "vwaitq\n"
                             "vmulq.xyz vf5, vf5, Q\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(&v) : "memory");
        f12 = (v.f[2] + 1.0f) * 0.5f;
    }
    func_000B0160(c, c + 0xD0, 0xC, f12);
}
#endif
