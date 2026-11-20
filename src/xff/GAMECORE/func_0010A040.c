typedef float Vec4[4] __attribute__((aligned(16)));

/* The store to p+0x60 goes through a union so it may alias the pointer
   load from w+0x1C that follows, as in the Original. */
typedef union {
    float f;
    int *q;
} FloatOrPtr;

extern char gcGlobalVar[];
extern int *ScriptCtrlDef_SCRStop;
extern int *ScriptCtrlDef_SCRGoL;
extern int *ScriptCtrlDef_SCRGoR;
extern int *ScriptCtrlDef_SCRDash;
extern int *ScriptCtrlDef_SCRFastR;
extern int *ScriptCtrlDef_SCRFastL;
extern float iosGetATan2fExact(float, float);
extern float adjustCurveAngleForCollision(void *actor, float angle, float threshold, float distance);
extern int chkAttainExecLayout(void *, void *, void *, void *);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
extern void func_0010A930(void *, int);
extern int func_0010A540(void *, int);
extern void func_0010A3F8(void *, int, float);

static inline void vecSub(void *d, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
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

static inline float vecLength(void *v)
{
    float r;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(v) : "$2");
    return r;
}

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

static void func_0010A040(char *w, int flag)
{
    Vec4 d;
    char *p;
    char *lay;
    char *tgt;
    int r;
    float len, ang, dang, ratio, lim, spd;

    p = *(char **)(w + 0xCC);
    lay = *(char **)(w + 4);
    tgt = p + 0x50;
    vecSub(d, tgt, *(void **)(*(char **)(w + 0x18) + 0x134));
    d[3] = 1.0f;
    applyMatrix(d, w + 0x20, d);
    d[1] = 0.0f;
    len = vecLength(d);
    vecNormalize(d);
    ang = iosGetATan2fExact(d[0], d[2]);
    ang = adjustCurveAngleForCollision(w, ang, 1.5707963f, 2.0f);
    dang = (ang - *(float *)(p + 0x60)) / *(float *)(gcGlobalVar + 0x190);
    spd = *(float *)(w + 0xA0);
    ((FloatOrPtr *)(p + 0x60))->f = ang;
    lim = 0.0523598753f;
    ratio = len / *(float *)(p + 0x88);
    dang *= spd;
    if (*(int *)(p + 0xB0) == **(int **)(w + 0x1C)) {
        if (1.3962634f < ang) {
            CharaCtrlSetScriptCtrlStatus(*(void **)(w + 8), ScriptCtrlDef_SCRFastR[1]);
        } else if (ang < -1.3962634f) {
            CharaCtrlSetScriptCtrlStatus(*(void **)(w + 8), ScriptCtrlDef_SCRFastL[1]);
        }
        return;
    } else {
        if (__builtin_fabsf(ang) / *(float *)(p + 0x64) < ratio
            && (flag == 0 || *(float *)(lay + 0x3F4) < len)
            && *(int *)(*(char **)(w + 0x14) + 0x750) == *(int *)(p + 0x20)) {
            func_0010A930(w, flag);
            return;
        }
        if ((lim < ang && -lim <= ang + dang)
            || (0.523598731f < *(float *)(w + 0x160) && 2.35619426f < __builtin_fabsf(ang))) {
            CharaCtrlSetScriptCtrlStatus(*(void **)(w + 8), ScriptCtrlDef_SCRGoR[1]);
            if (func_0010A540(w, flag) != 0)
                CharaCtrlSetScriptCtrlStatus(*(void **)(w + 8), ScriptCtrlDef_SCRDash[1]);
            return;
        } else if ((ang < -lim && ang + dang <= lim)
                   || (*(float *)(w + 0x160) < -0.523598731f && 2.35619426f < __builtin_fabsf(ang))) {
            CharaCtrlSetScriptCtrlStatus(*(void **)(w + 8), ScriptCtrlDef_SCRGoL[1]);
            if (func_0010A540(w, flag) != 0)
                CharaCtrlSetScriptCtrlStatus(*(void **)(w + 8), ScriptCtrlDef_SCRDash[1]);
            return;
        } else if (flag != 0) {
            r = chkAttainExecLayout(lay, tgt, *(void **)(w + 0x18), *(void **)(w + 0x14));
            if (*(int *)(lay + 0xE0) == 0 && r == 1) {
                CharaCtrlSetScriptCtrlStatus(*(void **)(w + 8), ScriptCtrlDef_SCRStop[1]);
                return;
            } else {
                func_0010A3F8(w, r, ang);
                return;
            }
        } else {
            if (*(int *)(*(char **)(w + 0x14) + 0x750) == *(int *)(p + 0x20))
                func_0010A930(w, 0);
            return;
        }
    }
}
