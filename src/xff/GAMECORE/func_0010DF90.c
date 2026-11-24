typedef float Vec4[4] __attribute__((aligned(16)));
typedef int u128 __attribute__((mode(TI)));
typedef struct {
    int x[8];
} __attribute__((aligned(8))) Blk;
typedef union {
    u128 q;
    int i[4];
} Q4;

extern char *ScriptCtrlDef_SCRStop;
extern char gcGlobalVar[];
extern int calcAttainPosForAttainRange(char *, int *, float *, float *, void *, int, int);
extern void calcAttainRangeData(void *, void *, int);
extern float iosGetATan2fExact(float, float);
extern void analyzeMotionProperty(int, int, void *, void *, void *, float, float);
extern void analyzeMotionPropertyFromKey2(char *, int, void *, void *, void *);
extern char *GetLayoutClass(int);
extern void GetMotionNodeQuaternionPos(float *, float *, int, int, int);
extern int moveCtrlClipCollisionDirect(float *, float *, void *, int, int);

static inline void vecSub(void *d, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void vecAdd(void *d, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void vecNormalize(void *d, void *s)
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
                         : : "r"(d), "r"(s) : "memory");
}

static inline void applyMatrix(void *d, void *m, void *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%2)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(d), "r"(m), "r"(v) : "memory");
}

static inline void vecUnit(void *d)
{
    __asm__ __volatile__("sqc2 $vf0, 0x0(%0)\n" : : "r"(d) : "memory");
}

static inline void quatAxisZ(void *d, void *q)
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
                         : : "r"(d), "r"(q) : "memory");
}

static inline void vecScale(void *d, void *s, float k)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(s), "r"(k) : "memory");
}

static void func_0010DF90(char *w)
{
    Vec4 d0, d1, d2, d3, p, q, e, pos, rot, end;
    int idx;
    char *own;
    char *m;

    *(int *)(w + 0x164) = 0;
    own = *(char **)(w + 0xCC);
    vecUnit(w + 0x170);
    *(int *)(w + 0x1C0) = 0;
    *(Blk *)(w + 0x1A0) = *(Blk *)(*(char **)(w + 4) + 0x3E0);
    if (*(void **)(w + 0xC) == 0)
        return;
    if (*(void **)(w + 0x10) != 0) {
        (*(Q4 *)(w + 0x190)).q = (**(Q4 **)(w + 0xC)).q;
        vecSub(d0, w + 0x190, *(char **)(w + 4) + 0x30);
        vecSub(d1, *(void **)(w + 0x10), w + 0x190);
    } else {
        if (calcAttainPosForAttainRange(w, &idx, p, q, *(void **)(w + 0xC), *(int *)(own + 0x3C), 1)) {
            *(int *)(w + 0x164) = 1;
            *(int *)(w + 0x1C0) = 1;
            (*(Q4 *)(w + 0x170)).q = (*(Q4 *)q).q;
            (*(Q4 *)(w + 0x190)).q = (*(Q4 *)p).q;
            calcAttainRangeData(w + 0x1A0, *(char **)(w + 4) + 0x3E0, idx);
        } else {
            (*(Q4 *)(w + 0x190)).q = (**(Q4 **)(w + 0xC)).q;
            *(int *)(w + 0x164) = *(int *)(*(char **)(w + 4) + 0xA8);
            (*(Q4 *)(w + 0x170)).q = (*(Q4 *)(*(char **)(w + 4) + 0xB0)).q;
        }
        vecSub(d0, w + 0x190, *(void **)(*(char **)(w + 0x18) + 0x134));
        (*(Q4 *)d1).q = (*(Q4 *)d0).q;
    }
    d0[3] = 1.0f;
    d1[3] = 1.0f;
    vecNormalize(d0, d0);
    vecNormalize(d1, d1);
    vecAdd(d2, d0, d1);
    d2[3] = 1.0f;
    vecNormalize(d2, d2);
    applyMatrix(w + 0xE0, w + 0x20, d2);
    applyMatrix(w + 0xD0, w + 0x20, d0);
    applyMatrix(w + 0xF0, w + 0x20, d1);
    applyMatrix(w + 0x100, w + 0x20, w + 0x190);
    applyMatrix(w + 0x110, w + 0x20, *(void **)(*(char **)(w + 0x18) + 0x134));
    applyMatrix(d3, w + 0x20, *(char **)(w + 0x18) + 0x30);
    *(float *)(w + 0xE4) = 0.0f;
    *(float *)(w + 0xD4) = 0.0f;
    *(float *)(w + 0xF4) = 0.0f;
    vecNormalize(w + 0xE0, w + 0xE0);
    vecNormalize(w + 0xD0, w + 0xD0);
    vecNormalize(w + 0xF0, w + 0xF0);
    if (*(int *)(w + 0x164) != 0) {
        applyMatrix(w + 0x180, w + 0x20, w + 0x170);
        *(float *)(w + 0x184) = 0.0f;
        vecNormalize(w + 0x180, w + 0x180);
        *(float *)(w + 0x15C) = iosGetATan2fExact(*(float *)(w + 0x180), *(float *)(w + 0x188));
    } else {
        *(float *)(w + 0x15C) = 0.0f;
    }
    m = *(char **)(w + 0x1C);
    *(float *)(w + 0x140) = 0.0f;
    *(float *)(w + 0x144) = 0.0f;
    *(float *)(w + 0x148) = 0.0f;
    *(float *)(w + 0x14C) = 0.0f;
    *(float *)(w + 0x150) = 0.0f;
    analyzeMotionProperty(*(int *)(w + 8), *(int *)m, w + 0x140, w + 0x144, 0, *(float *)(w + 0xB0), *(float *)(m + 0xC));
    analyzeMotionPropertyFromKey2(w, *(int *)(ScriptCtrlDef_SCRStop + 4), w + 0x14C, w + 0x150, 0);
    {
        /* The Original loads w->0x1C into $v1 here. */
        register int *q __asm__("$3") = *(int **)(w + 0x1C);

        analyzeMotionProperty(*(int *)(w + 8), *q, 0, 0, w + 0x148, 1.0f, 0.0f);
    }
    if (*(int *)(own + 0x30) == 0) {
        *(float *)(w + 0x1C8) = *(float *)(own + 0x44);
        *(float *)(w + 0x1CC) = *(float *)(own + 0x48);
        *(float *)(w + 0x1D0) = *(float *)(own + 0x80);
        *(float *)(w + 0x1D4) = *(float *)(own + 0x84);
    } else {
        *(float *)(w + 0x1C8) = *(float *)(own + 0x50);
        *(float *)(w + 0x1CC) = *(float *)(own + 0x54);
        *(float *)(w + 0x1D0) = *(float *)(own + 0x8C);
        *(float *)(w + 0x1D4) = *(float *)(own + 0x90);
    }
    if (*(int *)(w + 0x1D8) != 0) {
        char *l = GetLayoutClass(*(int *)(w + 0x1D8));
        vecSub(e, *(void **)(l + 0x134), *(void **)(*(char **)(w + 0x18) + 0x134));
        e[1] = 0.0f;
        vecNormalize(e, e);
        applyMatrix(e, w + 0x20, e);
        *(float *)(w + 0x1DC) = iosGetATan2fExact(e[0], e[2]);
    } else {
        *(float *)(w + 0x1DC) = 0.0f;
    }
    if (*(char **)(own + 0xA4) != 0) {
        GetMotionNodeQuaternionPos(rot, pos, *(int *)(w + 8), *(int *)(*(char **)(own + 0xA4) + 8), 1);
        quatAxisZ(end, *(void **)(*(char **)(w + 0x18) + 0x13C));
        vecScale(end, end, *(float *)(own + 0xA0));
        vecAdd(end, end, pos);
        *(int *)(w + 0x1E0) = moveCtrlClipCollisionDirect(pos, end, gcGlobalVar + 0x238, *(int *)(w + 0x14), *(int *)(w + 0x18));
    } else {
        *(int *)(w + 0x1E0) = 0;
    }
}
