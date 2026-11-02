typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4;

extern char *getSCRDataCtrlWork(void *);
extern char *GetLayoutClass(void *);
extern int getPassageNum(char *);
extern void *getColiGroupByUserPathWork(char *);
extern void *getRealColJudgeFunc(char *);
extern int ClipCollisionDirectCallBack(void *, void *, Vec4 *, void *, int, int, int, void *, int);

static inline void vecNormalize(void *v)
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

int SCRConditionNargaWallCheck2(void *obj, float dist)
{
    char *w = getSCRDataCtrlWork(obj);
    char *l = GetLayoutClass(obj);
    Vec4 v;
    char hit[0x50];

    if (getPassageNum(w) >= 2)
        return 0;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(&v), "r"(w + 0x70), "r"(*(void **)(l + 0x134)) : "memory");
    v.y = 0.0f;
    vecNormalize(&v);
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(&v), "r"(dist) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(&v), "r"(&v), "r"(*(void **)(l + 0x134)) : "memory");
    v.w = 1.0f;
    return ClipCollisionDirectCallBack(hit, *(void **)(l + 0x134), &v, getColiGroupByUserPathWork(w), 0, 0, 0,
                                       getRealColJudgeFunc(w), 0);
}
