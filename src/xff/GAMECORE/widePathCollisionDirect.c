/* Parked: 2 diffs, same size. Remaining: gcc schedules the mov.s $f22,$f21
 * (dL = dR = 0.0) before the grp spill store sw $v0,0xC8($sp); the Original
 * stores grp first. */

#ifdef NONMATCHING

typedef float Vec4[4] __attribute__((aligned(16)));
typedef unsigned int u_long128 __attribute__((mode(TI)));

typedef struct {
    char pad0[0x40];
    Vec4 pos;
} ClipResult;

extern int func_000FAEC8(void *);
extern int pathJudgeFunc();
extern int getPathColiGroupByType(int);
extern int getColiGroupByUserPathWork(void *);
extern Vec4 YUnitVector;
extern int ClipCollisionDirectCallBackDoubleSide(ClipResult *, float *, float *, int, int, int, int, int, int (*)(), int);

static inline void vecSub(float *dst, float *a, float *b)
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

static inline void vecCross(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
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

static inline void vecAddXYZ(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline float vecDist(float *a, float *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

int widePathCollisionDirect(char *work, float *start, float *end, int n, int flag, int extra, float width)
{
    ClipResult res;
    Vec4 side;
    Vec4 s0;
    Vec4 e0;
    Vec4 off;
    Vec4 a;
    Vec4 b;
    int cnt;
    int grp;
    int (*judge)();
    int hitR;
    int hitL;
    float dR;
    register float dL __asm__("$f22");
    int i;
    int r;

    r = getPathColiGroupByType(*(int *)(work + 0x3C50));
    if (r == 0)
        return r;
    if (ClipCollisionDirectCallBackDoubleSide(&res, start, end, getPathColiGroupByType(*(int *)(work + 0x3C50)), extra, func_000FAEC8(work), 0, 0, pathJudgeFunc, 0) != 0)
        return 1;
    r = 0;
    if (0.0f < width && n > 0) {
        cnt = n * 2 + 1;
        grp = getPathColiGroupByType(*(int *)(work + 0x3C50));
        dR = 0.0f;
        judge = pathJudgeFunc;
        __asm__("" : "=f"(dL) : "0"(dR));
        hitR = 0;
        hitL = 0;
        vecSub(side, end, start);
        vecNormalize(side);
        side[3] = 1.0f;
        vecCross(side, side, YUnitVector);
        vecNormalize(side);
        side[3] = dR;
        vecScale(off, side, -width);
        vecAddXYZ(s0, start, off);
        vecAddXYZ(e0, end, off);
        vecScale(side, side, width / (float)n);
        if (flag) {
            grp = getColiGroupByUserPathWork(work);
            judge = *(int (**)())(work + 0x3C54);
        }
        for (i = 0; i < cnt; i++) {
            if (i == n)
                continue;
            vecScale(off, side, (float)i);
            vecAddXYZ(a, s0, off);
            vecAddXYZ(b, e0, off);
            a[3] = 1.0f;
            b[3] = 1.0f;
            if (ClipCollisionDirectCallBackDoubleSide(&res, a, b, grp, extra, func_000FAEC8(work), 0, 0, judge, 0) != 0) {
                if (i < n) {
                    hitL = 1;
                    dL = vecDist(a, res.pos);
                    i = n;
                } else {
                    hitR = 1;
                    dR = vecDist(a, res.pos);
                    break;
                }
            }
        }
        if (hitR) {
            r = 2;
            if (hitL) {
                r = 5;
                if (dR < dL)
                    r = 4;
            }
            return r;
        }
        if (hitL)
            return 3;
    }
    return r;
}

#endif
