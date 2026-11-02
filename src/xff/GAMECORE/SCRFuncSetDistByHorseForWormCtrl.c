extern char gcGlobalVar[];
extern void *SCRGetFirstObj(void *);
extern float getHorseInterpSpeed(void *);
extern char *getSCRDataCtrlWork(void *);
extern int execCondition(void *, int);
extern char *GetLayoutClass(void *);
extern void setAttainSpeedWormCtrlWork(void *, float);

static inline float distXZ(float *a, float *b)
{
    float d;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "vsqrt Q, vf7x\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

int SCRFuncSetDistByHorseForWormCtrl(void *obj, int b, int c, int d, int e, int f, int cond, float minSpeed,
                                      float speed, float dist)
{
    float hs = getHorseInterpSpeed(SCRGetFirstObj(gcGlobalVar + 0x2B4));
    char *w = getSCRDataCtrlWork(obj);
    char *worm = w + 0x3D10;
    float diff;
    float s;

    if (*(int *)(w + 0x4090) == 3) {
        if (execCondition(obj, cond) && minSpeed <= hs) {
            diff = distXZ(*(float **)(GetLayoutClass(obj) + 0x134), *(float **)(*(char **)(w + 0x407C) + 0x134)) - dist;
            s = hs;
            if (__builtin_fabsf(diff) > 1.0f) {
                if (diff > 0.0f) {
                    s *= 1.2f;
                } else {
                    s *= 0.8f;
                }
            }
            setAttainSpeedWormCtrlWork(worm, s);
        } else {
            setAttainSpeedWormCtrlWork(worm, speed);
        }
    }
}
