typedef struct {
    char pad0[0x2B8];
    char bossList[1];
} GlobalVar;

extern GlobalVar gcGlobalVar;
extern void *SCRGetFirstObj(void *);
extern char *getSCRDataCtrlWork(void *);
extern char *GetLayoutClass(void *);
extern void iosGetStabXZVector(float *, float *);
extern void setAttainmentPos(char *, float *);

static inline void vecSub(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline void vecScaleXYZ(float *dst, float *src, float s)
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

void SCRFuncHorseEscapeFromBoss(void *obj, float distance)
{
    void *boss;
    char *work;
    char *layout;
    float dir[4] __attribute__((aligned(16)));

    boss = SCRGetFirstObj(gcGlobalVar.bossList);
    if (boss != 0) {
        work = getSCRDataCtrlWork(obj);
        layout = GetLayoutClass(obj);
        vecSub(dir, *(float **)(layout + 0x134), *(float **)(GetLayoutClass(boss) + 0x134));
        iosGetStabXZVector(dir, dir);
        vecScaleXYZ(dir, dir, distance);
        vecAddXYZ(dir, dir, *(float **)(GetLayoutClass(obj) + 0x134));
        dir[3] = 1.0f;
        setAttainmentPos(work, dir);
    }
}
