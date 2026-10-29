typedef int Qword __attribute__((mode(TI)));
typedef union { Qword q; float f[4]; } Vec4;
extern char *getSCRDataCtrlWork(void *);
extern char *GetLayoutClass(void *);
extern int getPassageNum(void *);
extern void *getColiGroupByUserPathWork(void *);
extern int getRealColJudgeFunc(void *);
extern int ClipCollisionDirectCallBack(void *, void *, void *, void *, int, int, int, int (*)(), int);
extern void setAttainmentPos(void *, void *);
static inline float distanceXZ(float *a, float *b)
{
    float distance;
    __asm__ __volatile__(
        "lqc2 vf5, 0(%1)\n" "lqc2 vf6, 0(%2)\n"
        "vsub.xyzw vf7, vf5, vf6\n"
        "vmul.xz vf7, vf7, vf7\n" "vaddz.x vf7, vf7, vf7z\n"
        "vsqrt Q, vf7x\n" "vwaitq\n" "cfc2 $2, $vi22\n"
        "mtc1 $2, %0\n"
        : "=f"(distance) : "r"(a), "r"(b) : "$2");
    return distance;
}

void SCRFuncNargaSetPlayerAttainmentPos(void *actor, float distance)
{
    Vec4 result[5];
    char *work = getSCRDataCtrlWork(actor);
    char *layout = GetLayoutClass(actor);
    void *group;
    int callback;
    if (getPassageNum(work) == 1) {
        group = getColiGroupByUserPathWork(work);
        callback = getRealColJudgeFunc(work);
        if (ClipCollisionDirectCallBack(result, *(void **)(layout + 0x134),
                *(void **)(*(char **)(work + 0x407C) + 0x134), group,
                0, 0, 0, (int (*)())callback, 0)) {
            if (distanceXZ(*(float **)(*(char **)(work + 0x407C) + 0x134), result[4].f) < distance) {
                setAttainmentPos(work, &result[4]);
                return;
            }
        }
    }
    setAttainmentPos(work, *(void **)(*(char **)(work + 0x407C) + 0x134));
}
