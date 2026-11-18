typedef int u128 __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } Vec4 __attribute__((aligned(16)));
typedef struct { char pad[4]; void *ctrl; } ScriptCtrlDef;
typedef struct {
    char pad0[4];
    char *lay;
    int chara;
    int c;
    int pad10;
    char *body;
    int e18;
} Work;

extern ScriptCtrlDef *ScriptCtrlDef_SCRStop;
extern ScriptCtrlDef *ScriptCtrlDef_SCRGoR;
extern ScriptCtrlDef *ScriptCtrlDef_SCRGoL;
extern float iosGetATan2fExact(float, float);
extern int chkAttainExecLayout(void *, int, int, void *);
extern void CharaCtrlSetScriptCtrlStatus(int, void *);
extern void func_0010B6B8(Work *, int);
extern float calcProgRotRatioForMove2(Work *, float);
extern void SCRCharaTurnDirectInput(int, float);

static inline void vecSub(Vec4 *d, Vec4 *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void vecAdd(Vec4 *d, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline float vecLength(Vec4 *v)
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

static inline void vecNormalize(Vec4 *v)
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

static inline float vecDot(Vec4 *a, Vec4 *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

static inline void vecScale(Vec4 *d, Vec4 *a, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(s) : "memory");
}

static void func_0010B200(Vec4 *pos, Vec4 *dir, int noTurn, int check, Work *w)
{
    Vec4 p;
    Vec4 d3;
    Vec4 d1;
    Vec4 v;
    Vec4 d2;
    char *lay;
    int stop;
    float len, dot1, dot2, ang, a, r;

    stop = 0;
    lay = w->lay;
    vecSub(&d1, pos, (char *)w + 0x110);
    d1.y = 0.0f;
    len = vecLength(&d1);
    vecNormalize(&d1);
    dot1 = vecDot(&d1, dir);
    vecAdd(&d2, &d1, dir);
    vecNormalize(&d2);
    dot2 = vecDot(&d2, dir);
    vecScale(&v, &d2, -(len * dot1 / dot2));
    *(u128 *)&p = *(u128 *)pos;
    vecSub(&d3, &p, (char *)w + 0x110);
    d3.y = 0.0f;
    vecLength(&d3);
    vecNormalize(&d3);
    ang = iosGetATan2fExact(d3.x, d3.z);
    if (check && *(int *)(lay + 0xE0) == 0 && chkAttainExecLayout(lay, w->c, w->e18, w->body) == 1) {
        CharaCtrlSetScriptCtrlStatus(w->chara, ScriptCtrlDef_SCRStop->ctrl);
        stop = 1;
    }
    if (!stop && !noTurn)
        func_0010B6B8(w, check);
    a = ang;
    if (a > 2.7925268173217774f && *(float *)(w->body + 0x72C) > 0.0f)
        a = -3.141592597961426f;
    else if (ang < -2.7925268173217774f && *(float *)(w->body + 0x72C) < 0.0f)
        a = 3.141592597961426f;
    r = calcProgRotRatioForMove2(w, a);
    if (r != 0.0f) {
        if (a > 0.1396263301372528f) {
            CharaCtrlSetScriptCtrlStatus(w->chara, ScriptCtrlDef_SCRGoR->ctrl);
            SCRCharaTurnDirectInput(w->chara, r);
        } else if (a < -0.1396263301372528f) {
            CharaCtrlSetScriptCtrlStatus(w->chara, ScriptCtrlDef_SCRGoL->ctrl);
            SCRCharaTurnDirectInput(w->chara, -r);
        }
    }
}
