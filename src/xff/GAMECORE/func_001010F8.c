typedef float Vec4[4] __attribute__((aligned(16)));
typedef unsigned int u_long128 __attribute__((mode(TI)));

extern float IdentityQuaternion[4];
extern int *ScriptCtrlDef_SCRAttack0;
extern int *ScriptCtrlDef_SCRBirdHoveringAttack;
extern int *ScriptCtrlDef_SCRFlapWing;
extern int *ScriptCtrlDef_SCRGlide;
extern int *ScriptCtrlDef_SCRHovering;
extern int *ScriptCtrlDef_SCRStop;
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
extern void GetQuaternionByEulerYXZ(float *, float, float, float);
extern float adjustAngleForLimit(float, float);
extern float calcAngleTime(float, float, float, float);
extern void calcMoveQuaternion(float *, float *, float *, float);
extern int chkMoveAngle(float, float);
extern void func_00100198(void *, char *);
extern void func_00100D78(void *, void *, float *, char *);
extern int func_001038C8(char *);
extern void getCalcAttackPassagePoint2(void *, char *);
extern int getPassageNum(char *);
extern void getTurnAndPitchFromDir(float *, float *, float *);
extern float iosGetASinfExact(float);

#define SETSTATUS(def) CharaCtrlSetScriptCtrlStatus(*(void **)(obj + 8), (def)[1])
#define WF(o) (*(float *)(wk + (o)))
#define WI(o) (*(int *)(wk + (o)))
#define OF(o) (*(float *)(obj + (o)))

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

static inline void quatZDir(float *dst, float *q)
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
                         : : "r"(dst), "r"(q) : "memory");
}

static inline float dot4(float *a, float *b)
{
    float r;

    __asm__ __volatile__("lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x0(%2)\n"
                         "vmul.xyzw vf15, vf14, vf15\n"
                         "vaddy.x vf15, vf15, vf15y\n"
                         "vaddz.x vf15, vf15, vf15z\n"
                         "vaddw.x vf15, vf15, vf15w\n"
                         "qmfc2.ni $2, vf15\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

static inline void negate4(float *v)
{
    float m = -1.0f;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v), "r"(m) : "memory");
}

static inline void lerpNorm(float *out, float *a, float *b, float t)
{
    __asm__ __volatile__("mfc1 $8, %3\n"
                         "qmtc2.ni $8, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyzw ACC, vf5, vf7x\n"
                         "vmaddw.xyzw vf9, vf6, vf8w\n"
                         "sqc2 vf9, 0x0(%0)\n"
                         "lqc2 vf14, 0x0(%0)\n"
                         "vmul.xyzw vf15, vf14, vf14\n"
                         "vaddy.x vf15, vf15, vf15y\n"
                         "vaddz.x vf15, vf15, vf15z\n"
                         "vaddw.x vf15, vf15, vf15w\n"
                         "vrsqrt Q, vf0w, vf15x\n"
                         "vwaitq\n"
                         "vmulq.xyzw vf15, vf14, Q\n"
                         "sqc2 vf15, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b), "f"(t) : "$8", "memory");
}

static inline void slerpTo(float *dst, float *q, float t)
{
    Vec4 c;
    float dv;
    *(u_long128 *)c = *(u_long128 *)dst;
    *(volatile float *)&dv = dot4(q, c);
    if (*(volatile int *)&dv < 0)
        negate4(c);
    lerpNorm(dst, q, c, t);
}

static void func_001010F8(u_long128 *pos, float *dir, int arg2, int arg3, int arg4, char *obj)
{
    Vec4 p;
    Vec4 d;
    Vec4 q;
    Vec4 mq;
    Vec4 z;
    float turn, pitch, turn2, pitch2;
    char *wk;
    char *pw;
    int go;
    int near;
    int ok;
    float len;

    go = 1;
    *(u_long128 *)p = *pos;
    __asm__ __volatile__("" : "=r"(wk) : "0"(*(char **)(obj + 0xCC)));
    pw = *(char **)(obj + 4);
    if (WI(0x30) != 0) {
        getCalcAttackPassagePoint2(p, obj);
        arg4 = 1;
    } else if (WI(0x3C) == 1) {
        arg4 = 1;
    }
    if (arg4 == 0) {
        if (getPassageNum(pw) == 2 && WI(0x154) == 1) {
            arg2 = 0;
            arg3 = 0;
            *(u_long128 *)p = *(u_long128 *)(obj + 0x110);
            __asm__ __volatile__("" ::: "memory");
            WI(0x40) = 1;
        } else {
            func_00100D78(p, pos, dir, obj);
        }
    } else if (*(int *)(pw + 0xE0) == 2) {
        func_00100198(p, obj);
    }
    vecSub(d, p, obj + 0x120);
    len = vecLength(d);
    vecNormalize(d, d);
    getTurnAndPitchFromDir(d, &turn, &pitch);
    {
        float a = OF(0x184);
        float s = pitch + a;
        if (__builtin_fabsf(s) >= 1.0471975f) {
            if (s >= 0.0f)
                pitch = 1.0471975f - a;
            else
                pitch = -1.0471975f - a;
        }
    }
    if (arg4 != 0) {
        if (WI(0x3C) == 1) {
            if (**(int **)(obj + 0x1C) == WI(0xD0)) {
                go = 0;
                SETSTATUS(ScriptCtrlDef_SCRBirdHoveringAttack);
            } else if (len < WF(0xD8)) {
                go = 0;
                if (WF(0xDC) > WF(0x224))
                    WF(0x22C) = OF(0x15C);
                if (len < WF(0xD8))
                    SETSTATUS(ScriptCtrlDef_SCRBirdHoveringAttack);
                else
                    SETSTATUS(ScriptCtrlDef_SCRGlide);
            }
        } else if (*(int *)(pw + 0xE0) == 0) {
            if (**(int **)(obj + 0x1C) == WI(0xC0)) {
                go = 0;
                SETSTATUS(ScriptCtrlDef_SCRStop);
            } else if (len < WF(0x104)) {
                go = 0;
                if (WF(0xCC) > WF(0x224))
                    WF(0x22C) = OF(0x15C);
                if (len < WF(0xC8))
                    SETSTATUS(ScriptCtrlDef_SCRStop);
                else
                    SETSTATUS(ScriptCtrlDef_SCRGlide);
            }
        } else if (WI(0x154) >= 2) {
            go = 0;
            if (WI(0x154) == 3 && WF(0x1A0) <= WF(0x190))
                SETSTATUS(ScriptCtrlDef_SCRAttack0);
            if (WF(0x1A4) > WF(0x224)) {
                WF(0x22C) = OF(0x15C);
                if ((unsigned int)(WI(0x154) - 2) < 2)
                    SETSTATUS(ScriptCtrlDef_SCRGlide);
                else if (WI(0x34) != 0)
                    SETSTATUS(ScriptCtrlDef_SCRFlapWing);
            } else {
                SETSTATUS(ScriptCtrlDef_SCRGlide);
            }
        }
    }
    if (go != 0) {
        float tt, ta, tb;
        near = 0;
        ok = 0;
        tt = len / WF(0x224);
        ta = calcAngleTime(turn, OF(0x148), *(float *)(*(char **)(obj + 0xCC) + 0x9C),
                           *(float *)(*(char **)(obj + 0xCC) + 0xA8));
        tb = calcAngleTime(pitch, OF(0x14C), *(float *)(*(char **)(obj + 0xCC) + 0x98),
                           *(float *)(*(char **)(obj + 0xCC) + 0xA8));
        if (ta * 1.05f <= tt && tb * 1.05f <= tt) {
            float lim = WF(0x9C);
            if (lim * 0.5f > __builtin_fabsf(turn) && WF(0x98) * 0.5f > __builtin_fabsf(pitch)) {
                float f = OF(0x1A0);
                near = 1;
                if (f == 0.0f || WF(0x78) <= f)
                    ok = 1;
            } else if (!(__builtin_fabsf(turn) < lim && __builtin_fabsf(pitch) < WF(0x98))) {
                arg2 = 1;
            }
        } else {
            arg2 = 1;
        }
        if (WF(0x94) > WF(0x224)) {
            WF(0x22C) = OF(0x15C);
            if (OF(0x15C) > -0.099999996f) {
                if (ok != 0) {
                    if (WI(0x34) != 0)
                        SETSTATUS(ScriptCtrlDef_SCRFlapWing);
                } else if (func_001038C8(obj) != 0) {
                    SETSTATUS(ScriptCtrlDef_SCRGlide);
                }
            } else if (WI(0x38) != 0) {
                SETSTATUS(ScriptCtrlDef_SCRHovering);
            }
        } else if (near != 0 && arg3 == 0) {
            if (WF(0x224) < WF(0x90)) {
                WF(0x22C) = OF(0x15C);
                if (OF(0x15C) > -0.099999996f && ok != 0 && WI(0x34) != 0)
                    SETSTATUS(ScriptCtrlDef_SCRFlapWing);
            }
        } else if (arg2 != 0) {
            float v = OF(0x160);
            if (v >= 0.0f && WI(0x38) != 0)
                SETSTATUS(ScriptCtrlDef_SCRHovering);
            else
                WF(0x22C) = v;
        } else {
            float v = OF(0x15C);
            if (0.0f < v)
                WF(0x22C) = 0.0f;
            else
                WF(0x22C) = v;
        }
    }
    if (WI(0x154) != 3 && **(int **)(obj + 0x1C) != WI(0xC0) && **(int **)(obj + 0x1C) != WI(0xD0)) {
        int lock = 0;
        float pp = pitch;
        float tu = turn;
        float h = OF(0x1A0);
        if (0.0f < h && 0.0f <= OF(0x184)) {
            float r = WF(0x6C);
            if (0.0f < r && h < r) {
                if (__builtin_fabsf(iosGetASinfExact(h / r)) < pp + OF(0x184))
                    lock = 1;
            }
        }
        calcMoveQuaternion(mq, IdentityQuaternion, (float *)(wk + 0x240), WF(0xA8));
        quatZDir(z, mq);
        getTurnAndPitchFromDir(z, &turn2, &pitch2);
        if (chkMoveAngle(turn2 * 1.05f, tu) != 0) {
            tu = 0.0f;
        } else {
            float l = WF(0x9C);
            float r = __builtin_fabsf(tu) / l;
            if (1.0f < r)
                r = 1.0f;
            if (tu < 0.0f)
                r = -r;
            tu = r * l;
        }
        if (lock != 0) {
            pp = -WF(0x98);
        } else {
            float a = OF(0x184);
            if (a >= 0.52359874f && pp < 0.0f) {
                pp = -WF(0x98);
            } else if (a >= 0.0f && pp < 0.0f && pp - a > -0.52359874f) {
                pp = -WF(0x98);
            } else if (a * (OF(0x184) + pp) < 0.0f && 0.6981317f < pp) {
                pp = WF(0x98);
            } else if (OF(0x184) * (OF(0x184) + pp) < 0.0f && pp < -0.6981317f) {
                pp = -WF(0x98);
            } else if (chkMoveAngle(pitch2 * 1.05f, pp) != 0) {
                pp = 0.0f;
            } else if (__builtin_fabsf(turn) >= 1.0471975f) {
                float a2 = OF(0x184);
                float s = a2 + pp;
                if (s >= 0.0f) {
                    if (0.26179937f < s)
                        pp = 0.26179937f - a2;
                    pp = adjustAngleForLimit(adjustAngleForLimit(pp, 0.26179937f), WF(0x98));
                } else {
                    pp = adjustAngleForLimit(pp / (turn / WF(0x9C)), WF(0x98) * 0.5f);
                }
            } else {
                float l = WF(0x98);
                float r = __builtin_fabsf(pp) / l;
                if (1.0f < r)
                    r = 1.0f;
                if (pp < 0.0f)
                    r = -r;
                pp = r * l;
            }
        }
        GetQuaternionByEulerYXZ(q, pp, tu, 0.0f);
        slerpTo((float *)(wk + 0x240), q, OF(0x150));
        GetQuaternionByEulerYXZ((float *)(wk + 0x260), pitch, turn, 0.0f);
    }
}
