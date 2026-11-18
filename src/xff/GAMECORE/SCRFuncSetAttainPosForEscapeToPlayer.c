/* Parked attempt (2 diffs): gcc puts the 0.017453293f constant for the
 * cos argument in $f21 instead of the Original's $f12 (mtc1/mul.s at
 * 0x124 and 0x130). Everything else matches. */
#ifdef NONMATCHING
typedef float Vec4[4] __attribute__((aligned(16)));
typedef unsigned int u_long128 __attribute__((mode(TI)));

typedef struct {
    char *area;
    unsigned *cnt;
    char pad[0x1C];
} PathArea;

typedef struct {
    PathArea a[4];
    char pad[0x90 - 4 * 0x24];
    int n;
} PathInfo;

extern char gcGlobalVar[];
extern float RO_00181640;
extern char *getSCRDataCtrlWork(void);
extern PathInfo *getPathInfo(char *);
extern void *SCRGetFirstObj(void *);
extern char *GetLayoutClass(void *);
extern float iosGetCosf(float);
extern u_long128 *getPointDataByAreaIdx(char *, unsigned, int);
extern void setAttainmentPos(char *, u_long128 *);

static inline void quatToDir(float *out, void *q)
{
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
                         : : "r"(out), "r"(q) : "memory");
}

static inline void vecSub(float *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float vecLength(float *v)
{
    float len;

    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(len) : "r"(v) : "$2");
    return len;
}

static inline void vecNormalize(float *dst, float *src)
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
                         : : "r"(dst), "r"(src) : "memory");
}

static inline float vecDot(float *a, float *b)
{
    float dot;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dot) : "r"(a), "r"(b) : "$2");
    return dot;
}

void SCRFuncSetAttainPosForEscapeToPlayer(float angle, float minDist)
{
    Vec4 dir;
    Vec4 toPlayer;
    Vec4 best;
    Vec4 tmp;
    int hasPlayer;
    char *ctrl;
    PathInfo *path;
    float bestDist;
    float c;
    float d;
    int i;
    unsigned j;

    ctrl = getSCRDataCtrlWork();
    hasPlayer = 0;
    path = getPathInfo(ctrl);
    quatToDir(dir, *(void **)(*(char **)(ctrl + 0x407C) + 0x13C));
    if (SCRGetFirstObj(gcGlobalVar + 0x2B8) != 0) {
        hasPlayer = 1;
        vecSub(toPlayer, *(void **)(GetLayoutClass(SCRGetFirstObj(gcGlobalVar + 0x2B8)) + 0x134),
               *(void **)(*(char **)(ctrl + 0x407C) + 0x134));
        vecNormalize(toPlayer, toPlayer);
        toPlayer[3] = 1.0f;
    }
    bestDist = 0.017453293f;
    c = iosGetCosf(angle * bestDist);
    bestDist = RO_00181640;
    for (i = 0; i < path->n; i++) {
        unsigned *cnt = path->a[i].cnt;
        int area = *(int *)(path->a[i].area + 0x1C);

        if (cnt != 0) {
            for (j = 0; j < *cnt; j++) {
                u_long128 *pt = getPointDataByAreaIdx(ctrl, j, area);

                vecSub(tmp, pt, *(void **)(*(char **)(ctrl + 0x407C) + 0x134));
                d = vecLength(tmp);
                tmp[1] = 0.0f;
                vecNormalize(tmp, tmp);
                tmp[3] = 1.0f;
                if (minDist < d && d < bestDist && vecDot(tmp, dir) < c
                    && (hasPlayer == 0 || vecDot(tmp, toPlayer) < c)) {
                    bestDist = d;
                    *(u_long128 *)best = *pt;
                }
            }
        }
    }
    if (bestDist != RO_00181640)
        setAttainmentPos(ctrl, (u_long128 *)best);
}
#endif
