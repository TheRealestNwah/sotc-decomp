typedef int s128 __attribute__((mode(TI)));

extern char *getSCRDataCtrlWork(void *);
extern float *getGoalPointDataByAreaIdx(void *, int, int);
extern float iosGetATan2fExact(float, float);
extern float adjustAnglePI(float);
extern void iosRotMatrixY(float *, float);
extern char ZDirVector[];
extern int setAttainmentPosAndDirAndLock(void *, float *, float *);

/* Parked attempt: 4 words differ from the Original. */
#ifdef NONMATCHING
/* 4 diffs: loop-top lwc1 RO_NoLimit/addu order, and the 2pi-span product lands in $f1 instead of $f0. */
static const unsigned int RO_NoLimit = 0xFFFFFFFF;
static inline void vecScaleXYZ(float *out, float *a, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "qmtc2.ni %2, vf6
"
                         "vmulx.xyz vf5, vf5, vf6x
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(out), "r"(a), "r"(s) : "memory");
}

static inline void vecAdd(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vadd.xyzw vf7, vf5, vf6
"
                         "sqc2 vf7, 0x0(%0)
"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

int func_000940A0(void *unused, float *lim)
{
    float v[4] __attribute__((aligned(16)));
    float m[16] __attribute__((aligned(16)));
    float p[4] __attribute__((aligned(16)));
    char *w = getSCRDataCtrlWork(unused);
    float *goal = getGoalPointDataByAreaIdx(w, *(int *)(w + 0x3C90), *(int *)(w + 0x3C8C));
    float cur, lo, hi, mid;
    int i, hit = 0;
    char *e8;

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
    e8 = (char *)lim + 8;
    for (i = 0; i < 3; i++) {
        float nl = *(const float *)&RO_NoLimit;
        int off = i * 8;
        float a;
        __asm__("" : "+r"(off));
        a = *(float *)(e8 + off);
        if (a != nl) {
        lo = a * 0.017453293f;
        hi = *(float *)((char *)lim + 0xC + off) * 0.017453293f;
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
            mid = (6.28318548f - (lo - hi)) * 0.5f; mid = adjustAnglePI(lo + mid);
            if (mid >= 0.0f) {
                if (lo <= cur) {
                    if (cur <= mid) cur = lo; else cur = hi;
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
                    if (cur <= mid) cur = lo; else cur = hi;
                    hit = 1;
                }
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
    vecScaleXYZ(p, v, *(float *)(w + 0x3C84));
    vecAdd(p, p, goal);
    vecScaleXYZ(v, v, -1.0f);
    return setAttainmentPosAndDirAndLock(w, p, v);
}
#endif
