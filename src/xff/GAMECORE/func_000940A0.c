typedef int s128 __attribute__((mode(TI)));

extern char *getSCRDataCtrlWork(void *);
extern float *getGoalPointDataByAreaIdx(void *, int, int);
extern float iosGetATan2fExact(float, float);
extern float adjustAnglePI(float);
extern void iosRotMatrixY(float *, float);
extern char ZDirVector[];
extern int setAttainmentPosAndDirAndLock(void *, float *, float *);

#ifdef NONMATCHING /* 130 diffs: saved-register assignment (orig hit=$s0 i=$s1 w=$s2 goal=$s3 lim=$s4 lim+8=$s5), frame 0xD0 vs 0xC0 */
static const unsigned int RO_NoLimit = 0xFFFFFFFF;
int func_000940A0(void *unused, float *lim)
{
    float v[4] __attribute__((aligned(16)));
    float m[16] __attribute__((aligned(16)));
    float p[4] __attribute__((aligned(16)));
    char *w = getSCRDataCtrlWork(0);
    float *goal = getGoalPointDataByAreaIdx(w, *(int *)(w + 0x3C90), *(int *)(w + 0x3C8C));
    float cur, lo, hi, mid;
    int i, hit = 0;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(v), "r"(w + 0x70), "r"(goal) : "memory");
    v[1] = 0.0f;
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
    cur = iosGetATan2fExact(v[0], v[2]);
    for (i = 0; i < 3; i++) {
        float a = *(float *)((char *)lim + 8 + i * 8);
        if (a == *(const float *)&RO_NoLimit)
            continue;
        lo = a * 0.017453293f;
        hi = *(float *)((char *)lim + 0xC + i * 8) * 0.017453293f;
        if (lo <= hi) {
            mid = lo + (hi - lo) * 0.5f;
            if (lo <= cur && cur <= mid) {
                cur = lo;
                hit = 1;
            } else if (mid <= cur && cur <= hi) {
                cur = hi;
                hit = 1;
            }
        } else {
            mid = adjustAnglePI(lo + (6.2831855f - (lo - hi)) * 0.5f);
            if (mid >= 0.0f) {
                if (lo <= cur) {
                    cur = (cur <= mid) ? lo : hi;
                    hit = 1;
                } else if (cur <= hi) {
                    cur = hi;
                    hit = 1;
                }
            } else {
                if (lo <= cur) {
                    cur = lo;
                    hit = 1;
                } else if (cur <= hi) {
                    cur = (cur <= mid) ? lo : hi;
                    hit = 1;
                }
            }
        }
        if (hit)
            break;
    }
    iosRotMatrixY(m, cur);
    __asm__ __volatile__("lqc2 vf8, 0x0(%1)\n"
                         "lqc2 vf14, 0x0(%2)\n"
                         "lqc2 vf15, 0x10(%2)\n"
                         "lqc2 vf16, 0x20(%2)\n"
                         "lqc2 vf17, 0x30(%2)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(v), "r"(ZDirVector), "r"(m) : "memory");
    {
        int sx = *(int *)(w + 0x3C84);
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "qmtc2.ni %2, vf6\n"
                             "vmulx.xyz vf5, vf5, vf6x\n"
                             "sqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%3)\n"
                             "vadd.xyzw vf7, vf5, vf6\n"
                             "sqc2 vf7, 0x0(%1)\n"
                             : : "r"(v), "r"(p), "r"(sx), "r"(goal) : "memory");
    }
    {
        int neg = 0xBF800000;
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "qmtc2.ni %1, vf6\n"
                             "vmulx.xyz vf5, vf5, vf6x\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(v), "r"(neg) : "memory");
    }
    return setAttainmentPosAndDirAndLock(w, p, v);
}
#endif
