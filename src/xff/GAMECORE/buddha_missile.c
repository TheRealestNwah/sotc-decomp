extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void *GetSCRCharaAIWorkPtr(void *);
extern float RO_0017D12C;
extern int *DldSysUndefSymbol;
extern char gcGlobalVar[];
extern char *getSCRDataCtrlWork(void *);
extern char *GetLayoutClass(void *);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
static inline char *dldElem(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}
extern float RO_0017D130;
typedef float Vec4[4] __attribute__((aligned(16)));
typedef unsigned int u_long128 __attribute__((mode(TI)));
typedef union {
    u_long128 q;
    Vec4 f;
} VecQ;
extern int SkelFocusDef_BUDDHA_OPT_ATTACK;
extern void SCRGetCharNodePos(float *, void *, int);
extern void GetQuaternionByAxisDirZY(float *, float *, float *);
extern void SCRSetupMissile1(void *, float *, float *, int);
static inline void vecDirection(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "lqc2 vf5, 0x0(%2)\n"
                         "vsub.xyzw vf6, vf4, vf5\n"
                         "vmul.xyz vf5, vf6, vf6\n"
                         "vaddy.x vf5, vf5, vf5y\n"
                         "vaddz.x vf5, vf5, vf5z\n"
                         "vsqrt Q, vf5x\n"
                         "vwaitq\n"
                         "vaddq.x vf5, vf0, Q\n"
                         "vdiv Q, vf0w, vf5x\n"
                         "vsub.xyzw vf7, vf0, vf0\n"
                         "vwaitq\n"
                         "vmulq.xyz vf7, vf6, Q\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static void func_0003FAD0(void *obj);

void SCRBuddhaShoot(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_0003FAD0);
}

void SCRFuncBuddhaMissileInit(void *actor)
{
    (*(float *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41B4)) = (float) RO_0017D12C;
}

void SCRFuncBuddhaMissileMain(void *actor, int a1, int a2, int a3, int a4, int a5, int a6, int a7, unsigned int *h)
{
    char *ai = GetSCRCharaAIWorkPtr(actor);
    char *data = getSCRDataCtrlWork(actor);
    char *layout = GetLayoutClass(actor);
    float d;
    float *tbl;
    char *e;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "vsqrt Q, vf7x\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(*(float **)(layout + 0x134)), "r"(*(float **)(*(char **)(data + 0x407C) + 0x134))
                         : "$2");
    tbl = *(float **)(ai + 0x41B0);
    if (tbl[0] <= d && d <= tbl[1]) {
        if (tbl[2] + (tbl[3] - tbl[2]) * ((d - tbl[0]) / (tbl[1] - tbl[0])) <= *(float *)(ai + 0x41B4)) {
            e = dldElem(h);
            if (e != 0)
                CharaCtrlSetScriptCtrlStatus(actor, *(int *)(e + 4));
            *(float *)(ai + 0x41B4) = 0;
            *(int *)(ai + 0x41C4) = 2;
        }
    }
    *(float *)(ai + 0x41B4) += *(float *)(gcGlobalVar + 0x180);
}

void SCRFuncBuddhaMissileInit2(void *actor)
{
    char *w = GetSCRCharaAIWorkPtr(actor);
    float *speed = (float *)(w + 0x41B4);
    float *src;

    *(int *)(w + 0x41BC) = 1;
    *speed = *(src = &RO_0017D130);
    *(int *)(w + 0x41B8) = 0;
    *(int *)(w + 0x41C0) = 0;
}

void SCRFuncBuddhaMissileMain2(void *actor, int aim, int count, int a3, int a4, int a5, int a6, int a7, unsigned int *h,
                               float interval, float angle, float wait)
{
    char *ai = GetSCRCharaAIWorkPtr(actor);
    char *e;

    if (*(int *)(ai + 0x41BC) != 0) {
        if (*(float *)(ai + 0x41B8) <= 0.0f) {
            e = dldElem(h);
            if (e != 0)
                CharaCtrlSetScriptCtrlStatus(actor, *(int *)(e + 4));
            if (aim == 0) {
                *(int *)(ai + 0x41C4) = 2;
            } else {
                *(float *)(ai + 0x41C8) = angle;
                *(int *)(ai + 0x41C4) = 3;
            }
            *(float *)(ai + 0x41B8) = interval;
            if (++*(int *)(ai + 0x41C0) >= count) {
                *(float *)(ai + 0x41B4) = 0.0f;
                *(int *)(ai + 0x41BC) = 0;
                *(float *)(ai + 0x41B8) = 0.0f;
                *(int *)(ai + 0x41C0) = 0;
            }
        }
        *(float *)(ai + 0x41B8) -= *(float *)(gcGlobalVar + 0x180);
    } else {
        if (wait <= *(float *)(ai + 0x41B4))
            *(int *)(ai + 0x41BC) = 1;
        *(float *)(ai + 0x41B4) += *(float *)(gcGlobalVar + 0x180);
    }
}

static void func_0003FAD0(void *obj)
{
    char *w = GetSCRCharaAIWorkPtr(obj);
    Vec4 q;
    Vec4 pos;
    Vec4 dir;
    VecQ tgt;

    SCRGetCharNodePos(pos, obj, SkelFocusDef_BUDDHA_OPT_ATTACK);
    if (*(int *)(w + 0x41C4) == 2) {
        vecDirection(dir, *(float **)(*(char **)(w + 0x408C) + 0x134), pos);
    } else {
        tgt.q = **(u_long128 **)(*(char **)(w + 0x408C) + 0x134);
        tgt.f[1] += *(float *)(w + 0x41C8);
        vecDirection(dir, tgt.f, pos);
    }
    GetQuaternionByAxisDirZY(q, dir, dir);
    SCRSetupMissile1(obj, pos, q, *(int *)(w + 0x41C4));
}
