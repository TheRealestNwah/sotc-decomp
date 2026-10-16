/* Three consecutive functions from one original file. Each copies its own
   static copy of the same arena centre, so the constants stay separate. */
typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4;

extern char *getSCRDataCtrlWork(void *);
extern char *GetSCRCharaAIWorkPtr(void *);
extern void func_000D1A80(void *, Vec4 *, int, int);
extern void setAttainmentPosAndDirAndLock(void *, Vec4 *, Vec4 *);
extern void setPosGazeCtrlWork(void *, void *);
extern void updateAimIKWork(void *, Vec4 *);

static const Vec4 RO_00180DE0 = { -965.0f, -69.5f, 950.0f, 1.0f };
static const Vec4 RO_00180DF0 = { -965.0f, -69.5f, 950.0f, 1.0f };
static const Vec4 RO_00180E00 = { -965.0f, -69.5f, 950.0f, 1.0f };

static inline void vecSubW(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vsub.xyzw vf7, vf5, vf6
"
                         "sqc2 vf7, 0x0(%0)
"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vecNormalize(void *v)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)
"
                         "vmul.xyz vf7, vf5, vf5
"
                         "vmulax.w ACC, vf0, vf7x
"
                         "vmadday.w ACC, vf0, vf7y
"
                         "vmaddz.w vf7, vf0, vf7z
"
                         "vrsqrt Q, vf0w, vf7w
"
                         "vwaitq
"
                         "vmulq.xyz vf5, vf5, Q
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(v) : "memory");
}

void SCRFuncYamoriBSetAttainPos(void *obj, int b, int ev)
{
    char *w = getSCRDataCtrlWork(obj);
    Vec4 center = RO_00180DE0;
    Vec4 pos;
    Vec4 dir;

    func_000D1A80(obj, &pos, 1, ev);
    vecSubW(&dir, &pos, &center);
    dir.y = 0.0f;
    vecNormalize(&dir);
    dir.w = 1.0f;
    setAttainmentPosAndDirAndLock(w, &center, &dir);
}

void SCRFuncYamoriBSetAttainPosForGroundAttack(void *obj)
{
    char *w = getSCRDataCtrlWork(obj);
    Vec4 pos = RO_00180DF0;
    Vec4 dir;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(&dir), "r"(w + 0x4030), "r"(&pos) : "memory");
    dir.y = 0.0f;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(&dir) : "memory");
    dir.w = 1.0f;
    setPosGazeCtrlWork(w + 0x3CC0, w + 0x4030);
    setAttainmentPosAndDirAndLock(w, &pos.x, &dir.x);
}

void SCRFuncYamoriBAimInit(void *obj, float a, float dist)
{
    char *w = GetSCRCharaAIWorkPtr(obj) + 0x41F0;
    Vec4 center = RO_00180E00;
    Vec4 aim;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(&aim), "r"(w), "r"(&center) : "memory");
    aim.y = 0.0f;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(&aim) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(&aim), "r"(dist) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(&aim), "r"(&aim), "r"(w) : "memory");
    aim.w = 1.0f;
    updateAimIKWork(obj, &aim);
}
