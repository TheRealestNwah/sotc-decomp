extern int *DldSysUndefSymbol;
extern void analyzeMotionProperty(int, int, void *, void *, void *, float, float);
extern void _setStopCtrlModeBaseMoveWork(char *, int);
static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}
#define R(o) ((int)dldResolve((unsigned int *)(s + (o))))
typedef union { float f; unsigned int u; } U;
#define F(o) (((U *)(w + (o)))->f)
#define I(o) (*(int *)(w + (o)))
#define SF(o) (*(float *)(s + (o)))
/* Per-frame update of the slow-leg move controller: builds a base-move work block on the stack, turns the character quaternion into a matrix and its inverse, steers by direct input, then either keeps the passage target, clears it (no target), or checks whether the layout target is reached; when not reached it re-checks from the work position with the layout block temporarily swapped, picks the motion with func_0010E5A8 and applies scale. The matrix pointer is pinned to v1 so the quaternion pointer takes v0 like the Original. The x1C4 store goes through a union with long so it aliases the layout block's ld/sd copy and stays before the restore. */
typedef int s128 __attribute__((mode(TI)));
typedef struct {
    int x[4];
    char *q[4];
} __attribute__((aligned(8))) Blk;
typedef struct {
    char pad0[0xC];
    s128 *target;
    int x10;
    char *chr;
    int x18;
    char pad1C[4];
    float mat[4][4] __attribute__((aligned(16)));
    float inv[4][4] __attribute__((aligned(16)));
    char padA0[4];
    float a4;
    char padA8[0xCC - 0xA8];
    void *owner;
    char padD0[0x158 - 0xD0];
    float x158;
    float x15C;
    float x160;
    char pad164[0x190 - 0x164];
    s128 pos;
    Blk blk;
    int x1C0;
    float x1C4;
    char pad1C8[0x1D8 - 0x1C8];
    int x1D8;
    char pad1DC[0x1F0 - 0x1DC];
} Tmp;
typedef struct {
    char pad0[4];
    int x4;
    char pad8[8];
    s128 x10;
    int x20;
    char pad24[0x40 - 0x24];
    float x40;
} Ctrl;
typedef struct {
    char pad0[0xA8];
    int xA8;
    char padAC[0xE0 - 0xAC];
    int xE0;
    float xE4;
    char padE8[0x3E0 - 0xE8];
    Blk blk;
} Lay;
extern s128 fltMaxVector;
extern void _initBaseMoveTmpWork(void *, Tmp *, Ctrl *, Lay *);
extern void iosInverseMatrix(void *, void *);
extern void SCRCharaTurnDirectInput(void *, float);
extern int _compPassagePos(Tmp *);
extern int func_0010E5A8(Tmp *, int, int);
extern int setLockPassageWork(Lay *, int);
extern int chkAttainExecLayout(Lay *, s128 *, int, char *);
extern void _setAttainFlagBaseMoveWork(Ctrl *, int);
static inline void quatToMatrix(float *out, float *quat)
{
    __asm__ __volatile__("vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%1)\n"
                         "vmr32.w vf14, vf0\n"
                         "vmr32.w vf15, vf0\n"
                         "vmr32.w vf16, vf0\n"
                         "vopmula.xyz ACC, vf11, vf12\n"
                         "vmadd.xyz vf11, vf0, vf0\n"
                         "vmadd.xyz vf10, vf11, vf12\n"
                         "vmul.xyz vf13, vf11, vf10\n"
                         "vopmula.xyz ACC, vf11, vf10\n"
                         "vmaddw.xyz vf15, vf10, vf11w\n"
                         "vmsubw.xyz vf16, vf10, vf11w\n"
                         "vopmula.xyz ACC, vf13, vf12\n"
                         "vmadd.xyz vf17, vf13, vf12\n"
                         "vopmula.xyz ACC, vf15, vf12\n"
                         "vmadd.xyz vf15, vf0, vf0\n"
                         "vsub.xyz vf14, vf12, vf17\n"
                         "vmove.yz vf17, vf14\n"
                         "vmove.y vf14, vf16\n"
                         "vmove.y vf16, vf15\n"
                         "vmove.y vf15, vf17\n"
                         "vmove.z vf14, vf15\n"
                         "vmove.z vf15, vf16\n"
                         "vmove.z vf16, vf17\n"
                         "sqc2 vf14, 0x0(%0)\n"
                         "sqc2 vf15, 0x10(%0)\n"
                         "sqc2 vf16, 0x20(%0)\n"
                         : : "r"(out), "r"(quat));
}
static inline void unitRow(float *out)
{
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(out));
}
static inline void matInverse(float *dst, float *src)
{
    __asm__ __volatile__("lqc2 vf24, 0x30(%1)\n"
                         "vsubw.x vf25, vf0, vf0w\n"
                         "vmulx.xyz vf28, vf24, vf25x\n"
                         "vsub.w vf28, vf28, vf28\n"
                         "lq $8, 0x0(%1)\n"
                         "lq $9, 0x10(%1)\n"
                         "lq $10, 0x20(%1)\n"
                         "qmfc2.ni $11, vf0\n"
                         "pextlw $12, $9, $8\n"
                         "pextuw $13, $9, $8\n"
                         "pextlw $14, $11, $10\n"
                         "pextuw $15, $11, $10\n"
                         "pcpyld $8, $14, $12\n"
                         "pcpyud $9, $12, $14\n"
                         "pcpyld $10, $15, $13\n"
                         "pcpyud $11, $13, $15\n"
                         "qmtc2.ni $8, vf24\n"
                         "qmtc2.ni $9, vf25\n"
                         "qmtc2.ni $10, vf26\n"
                         "vmulax.xyzw ACC, vf24, vf28x\n"
                         "vmadday.xyzw ACC, vf25, vf28y\n"
                         "vmaddaz.xyzw ACC, vf26, vf28z\n"
                         "vmaddw.xyzw vf29, vf0, vf28w\n"
                         "vsub.w vf29, vf29, vf29\n"
                         "vadd.w vf29, vf29, vf0\n"
                         "sqc2 vf24, 0x0(%0)\n"
                         "sqc2 vf25, 0x10(%0)\n"
                         "sqc2 vf26, 0x20(%0)\n"
                         "sqc2 vf29, 0x30(%0)\n"
                         : : "r"(dst), "r"(src) : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
}
typedef float Vec4[4] __attribute__((aligned(16)));
typedef int u128 __attribute__((mode(TI)));
typedef struct {
    int x[8];
} __attribute__((aligned(8))) Blk_func_0010DF90;
typedef union {
    u128 q;
    int i[4];
} Q4;
extern char *ScriptCtrlDef_SCRStop;
extern char gcGlobalVar[];
extern int calcAttainPosForAttainRange(char *, int *, float *, float *, void *, int, int);
extern void calcAttainRangeData(void *, void *, int);
extern float iosGetATan2fExact(float, float);
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
extern void CharaCtrlSetScriptCtrlStatus(int, int);
extern float calcProgRotRatioForMove2(void *, float);
extern char *ScriptCtrlDef_SCRGoL;
extern char *ScriptCtrlDef_SCRGoR;
/* Root scale ratio update: clamps o->r (0x160) toward the chara's current ratio by a per-frame step, limits it to [p->f58, p->f38], eases it with getValueInterp and, when shrinking, limits it by the two analyzeMotionProperty2 speeds, then hands it to SCRSetRootScaleRatio / SCRSetCharaRootTurnScaleRatio. The analyzeMotionProperty2 prototype lists its float arguments before the pointers so gcc sets them up in the Original order. Mot's elem shares a union with a float so its load stays after the v[1] store, as in the Original. */
typedef struct { char pad0[0x360]; char b360; char pad361[2]; char b363; char pad364[0x20C]; float f570; char pad574[0x1DC]; int i750; }
Chara;
typedef struct { union { char *elem; float f0; } u; int pad4; float f8; float fC; } Mot;
typedef struct { char pad0[0x38]; float f38; char pad3C[0x1C]; float f58; float f5C; float f60; char pad64[8]; int i6C; char pad70[4]; float f74; float f78; char pad7C[0x1C]; int i98; } Prm;
typedef struct { char pad0[8]; int h; char padC[8]; Chara *c; char pad18[4]; Mot *m; char pad20[0xAC]; Prm *p; char padD0[0x74]; float f144; float f148; char pad14C[0x14]; float r; } Obj;
typedef struct { char pad0[0x190]; float f190; } GV;
extern void analyzeMotionProperty2(int, char *, float, float, float, float *, float *, float *);
extern float getValueInterp(float, float, float, float);
extern void SCRSetRootScaleRatio(int, float);
extern void SCRSetCharaRootTurnScaleRatio(int, float);
extern float fabsf(float);
typedef struct { int pad0; int status; } ScriptCtrlDef;
extern ScriptCtrlDef *ScriptCtrlDef_SCRAccel;
extern ScriptCtrlDef *ScriptCtrlDef_SCRDash;
extern ScriptCtrlDef *ScriptCtrlDef_SCRStopL;
extern ScriptCtrlDef *ScriptCtrlDef_SCRStopR;
extern ScriptCtrlDef *ScriptCtrlDef_SCRFastL;
extern ScriptCtrlDef *ScriptCtrlDef_SCRFastR;
extern ScriptCtrlDef *ScriptCtrlDef_SCRBack;
extern ScriptCtrlDef *ScriptCtrlDef_SCRTransL;
extern ScriptCtrlDef *ScriptCtrlDef_SCRTransR;
extern float adjustAnglePI(float);
extern int _resetBaseMoveWork(int a, char *p);
extern char *GetCharacterClass(int);
typedef unsigned int u_long128 __attribute__((mode(TI)));
typedef union {
    u_long128 q;
    float f[4];
} Vec4_func_0010FA90;
#define W(type, o) (*(type *)(p + (o)))
static inline void matApply(void *dst, void *m, void *v)
{
    __asm__ __volatile__("lqc2 vf08, 0x0(%2)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf08x\n"
                         "vmadday.xyzw ACC, vf15, vf08y\n"
                         "vmaddaz.xyzw ACC, vf16, vf08z\n"
                         "vmaddw.xyzw vf10, vf17, vf08w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(dst), "r"(m), "r"(v) : "memory");
}
static inline float vecLen(void *v)
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
static inline void vecNormalize1(void *v)
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
extern float calcAngleTime(float, float, float, float);
extern void PredictMotionGeometryPotentialWithScaleElem(void *, float *, int, int, float, float);

static void func_0010DF90(char *w);
static void func_0010F110(char *c, int mode, float ang);
static void func_0010F338(Obj *o);
static void func_0010F710(char *c, int mode);
static void func_0010FA18(int obj, char *w);
static void func_0010FA88(char *p);
static void func_0010FA90(char *p, u_long128 *target);

void createSlowLegCtrlWork(int mot, char *w, unsigned int *h)
{
    unsigned int v;
    int off;
    int *t;
    char *s;

    v = *h;
    off = v & 0x3FFFF;
    t = off != 0 ? *(int **)((char *)h - off) : 0;
    s = (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] : 0;
    ((void (*)(int, char *, int *))func_0010FA18)(mot, w, t);
    analyzeMotionProperty(mot, R(8), w + 0x44, w + 0x48, 0, 1.0f, 0.0f);
    if (R(0x10) != 0) {
        analyzeMotionProperty(mot, R(0x10), w + 0x50, w + 0x54, 0, 1.0f, 0.0f);
    } else {
        I(0x50) = 0;
        I(0x54) = 0;
    }
    F(0x4C) = SF(0) * 0.0174532924f;
    F(0x58) = SF(0x18);
    F(0x38) = 1.0f;
    F(0x5C) = SF(0x1C);
    F(0x60) = SF(0x20);
    analyzeMotionProperty(mot, R(4), 0, 0, w + 0x88, 1.0f, 0.0f);
    F(0x88) = __builtin_fabsf(F(0x88));
    _setStopCtrlModeBaseMoveWork(w, R(0x24));
    I(0x64) = R(0x2C);
    I(0x6C) = R(0x28);
    I(0x70) = R(0x34);
    if (R(0xC) != 0) {
        I(0x7C) = 1;
        analyzeMotionProperty(mot, R(0xC), w + 0x80, 0, w + 0x84, 1.0f, 0.0f);
        F(0x80) = __builtin_fabsf(F(0x80));
        F(0x84) = __builtin_fabsf(F(0x84));
    } else {
        I(0x7C) = 0;
        F(0x80) = 0.0f;
        F(0x84) = 0.0f;
    }
    if (R(0x14) != 0) {
        analyzeMotionProperty(mot, R(0x14), w + 0x8C, 0, w + 0x90, 1.0f, 0.0f);
        F(0x90) = __builtin_fabsf(F(0x90));
    } else {
        I(0x8C) = 0;
        F(0x90) = 0.0f;
    }
    if (R(0x30) != 0) {
        analyzeMotionProperty(mot, R(0x30), w + 0x68, 0, 0, 1.0f, 0.0f);
    } else {
        I(0x68) = 0;
    }
    F(0xA0) = SF(0x3C);
    {
        unsigned int *hh = (unsigned int *)(s + 0x38);
        unsigned int vv = *hh;
        int oo = vv & 0x3FFFF;
        t = oo != 0 ? *(int **)((char *)hh - oo) : 0;
        I(0xA4) = (t != 0 && t != DldSysUndefSymbol) ? (int)((char *)t[4] + ((vv >> 18) & 0xFFF) * ((int *)t[2])[3]) : 0;
    }
}

void updateSlowLegCtrlWork(void *th, Ctrl *ctrl, Lay *lay, int arg3)
{
    Tmp w;
    Tmp *p = &w;
    Tmp *b = &w;
    Blk save;
    int r;

    _initBaseMoveTmpWork(th, p, ctrl, lay);
    p->x1D8 = arg3;
    p->owner = ctrl;
    {
        register float *m __asm__("$3") = w.mat[0];
        quatToMatrix(m, (float *)(w.chr + 0x470));
        m += 12;
        unitRow(m);
    }
    matInverse(b->mat[0], b->mat[0]);
    iosInverseMatrix(b->inv, b->mat);
    ((void (*)(Tmp *))func_0010DF90)(p);
    SCRCharaTurnDirectInput(th, 0.0f);
    if (_compPassagePos(p) != 0) {
        ctrl->x10 = *b->target;
        ((void (*)(Ctrl *))func_0010FA88)(ctrl);
    }
    if (ctrl->x4 == 0) {
        ctrl->x10 = fltMaxVector;
        ((void (*)(Ctrl *))func_0010FA88)(ctrl);
        p->x160 = ctrl->x40;
        ctrl->x40 = 1.0f;
    } else if (b->target != 0) {
        if (b->x10 != 0) {
            ((void (*)(Tmp *, s128 *, int))func_0010FA90)(p, &p->pos, 0);
            {
                int m = func_0010E5A8(p, 0, 0);
                if (0.0f < b->a4)
                    ((void (*)(Tmp *, int, float))func_0010F110)(p, m, p->x158);
                ((void (*)(Tmp *, int))func_0010F710)(p, m);
            }
        } else {
            Blk *bp;
            ((void (*)(Tmp *, s128 *, int))func_0010FA90)(p, &p->pos, 0);
            setLockPassageWork(lay, 1);
            bp = &lay->blk;
            r = chkAttainExecLayout(lay, b->target, b->x18, b->chr);
            if (*(int *)(b->chr + 0x750) == ctrl->x20 && b->a4 == 0.0f && r == 1
                && (lay->xA8 == 0 || lay->xE0 != 0 || __builtin_fabsf(p->x15C) < lay->xE4)) {
                setLockPassageWork(lay, 0);
                _setAttainFlagBaseMoveWork(ctrl, 1);
            } else {
                if (p->x1C0 != 0) {
                    save = *bp;
                    *bp = p->blk;
                    r = chkAttainExecLayout(lay, &p->pos, b->x18, b->chr);
                    ((union { float f; long l; } *)&p->x1C4)->f = *(float *)((char *)bp + 0x14);
                    *bp = save;
                } else {
                    p->x1C4 = *(float *)((char *)bp + 0x14);
                }
                {
                    int m = func_0010E5A8(p, 1, r);
                    ((void (*)(Tmp *, int))func_0010F710)(p, m);
                    if (0.0f < b->a4)
                        ((void (*)(Tmp *, int, float))func_0010F110)(p, m, p->x158);
                }
            }
        }
    } else {
        p->x160 = 1.0f;
    }
    ((void (*)(Tmp *))func_0010F338)(p);
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
    *(Blk_func_0010DF90 *)(w + 0x1A0) = *(Blk_func_0010DF90 *)(*(char **)(w + 4) + 0x3E0);
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

static void func_0010F110(char *c, int mode, float ang)
{
    float v[4] __attribute__((aligned(16)));
    char *a = *(char **)(c + 0xCC);
    char *b = *(char **)(c + 0x14);
    float r = 0.0f;

    if (*(int *)(b + 0x750) == *(int *)(a + 0x70)) {
        if (*(int *)(a + 0x34) == 1) {
            __asm__ __volatile__("lqc2 vf8, 0x0(%1)\n"
                                 "lqc2 vf14, 0x0(%2)\n"
                                 "lqc2 vf15, 0x10(%2)\n"
                                 "lqc2 vf16, 0x20(%2)\n"
                                 "lqc2 vf17, 0x30(%2)\n"
                                 "vmulax.xyzw ACC, vf14, vf8x\n"
                                 "vmadday.xyzw ACC, vf15, vf8y\n"
                                 "vmaddaz.xyzw ACC, vf16, vf8z\n"
                                 "vmaddw.xyzw vf10, vf17, vf8w\n"
                                 "sqc2 vf10, 0x0(%0)\n"
                                 : : "r"(v), "r"(*(char **)(c + 4) + 0xB0), "r"(c + 0x20) : "memory");
            v[1] = r;
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
            ang = iosGetATan2fExact(v[0], v[2]);
        } else if (mode != 3 || *(float *)(b + 0x570) != r) {
            if (ang >= r) {
                if (ang >= 1.5707963f)
                    ang -= 1.5707963f;
                else
                    ang += -1.5707963f;
            } else if (ang <= -1.5707963f) {
                ang -= -1.5707963f;
            } else {
                ang += 1.5707963f;
            }
        }
    } else if ((unsigned)(mode - 4) < 2U) {
        if (ang >= r)
            ang += -3.1415927f;
        else
            ang += 3.1415927f;
    }
    r = calcProgRotRatioForMove2(c, ang);
    if (r != 0.0f) {
        if (ang > 0.0523598775f) {
            CharaCtrlSetScriptCtrlStatus(*(int *)(c + 8), *(int *)(ScriptCtrlDef_SCRGoR + 4));
            ((void (*)(int, float))SCRCharaTurnDirectInput)(*(int *)(c + 8), r);
            return;
        }
        if (ang < -0.0523598775f) {
            CharaCtrlSetScriptCtrlStatus(*(int *)(c + 8), *(int *)(ScriptCtrlDef_SCRGoL + 4));
            ((void (*)(int, float))SCRCharaTurnDirectInput)(*(int *)(c + 8), -r);
        }
    }
}

static void func_0010F338(Obj *o)
{
    float v[3];
    Prm *p = o->p;
    float cur = o->c->f570;
    float r, step, t, d;
    Chara *c;

    ((void (*)(int, char *, float *, float *, float *, float, float))analyzeMotionProperty)(o->h, o->m->u.elem, 0, 0, v, 1.0f, 0.0f);
    if (!((*(unsigned int *)(o->m->u.elem + 0x68) >> 4) & 1)) {
        o->r = 1.0f;
    } else {
        c = o->c;
        if (c->b360 == 0 && c->b363 != 0 && v[0] != 0.0f) {
            if (p->f78 != o->r && fabsf(p->f78 - o->r) <= 0.02f)
                o->r = p->f78;
        }
    }
    p->f78 = o->r;
    if (o->r != cur) {
        step = p->f5C * (*(GV *)&gcGlobalVar).f190;
        if (cur < o->r) {
            if (o->c->i750 == p->i6C && fabsf(o->f148) > 0.052359877f && o->f144 > 0.01f) {
                t = fabsf(o->r - cur) / o->f144 * (*(GV *)&gcGlobalVar).f190;
                if (t < step)
                    step = t;
            }
            if (step < o->r - cur)
                o->r = cur + step;
        } else if (o->r < cur && -step > o->r - cur) {
            o->r = cur - step;
        }
    }
    if (p->f38 < o->r)
        o->r = p->f38;
    else if (o->r < p->f58)
        o->r = p->f58;
    o->r = getValueInterp(p->f74, o->r - cur, p->f60, (*(GV *)&gcGlobalVar).f190) + cur;
    if (p->f38 < o->r)
        o->r = p->f38;
    else if (o->r < p->f58)
        o->r = p->f58;
    d = o->r - cur;
    if (d < 0.0f && (p->i98 != 0 || o->c->b363 != 0)) {
        if (o->m->fC != 0.0f) {
            if (v[0] != 0.0f) {
            analyzeMotionProperty2(o->h, o->m->u.elem, 1.0f, 0.0f, o->m->fC, 0, 0, &v[1]);
            v[1] *= cur;
            analyzeMotionProperty2(o->h, o->m->u.elem, 1.0f, 0.0f, o->m->f8, 0, 0, &v[2]);
            {
                float rr = o->r, a = v[1], b = v[2];
                float t = b * rr;
                if ((a > 0.0f && t < a) || (a < 0.0f && a < t)) {
                    if (b != 0.0f)
                        o->r = fabsf(a / b);
                    else
                        o->r = cur;
                }
            }
            if (p->f38 < o->r)
                o->r = p->f38;
            }
        } else {
            o->r = cur;
        }
        d = o->r - cur;
    }
    p->f74 = d;
    __asm__ volatile("" ::: "memory");
    p->i98 = o->c->b363;
    __asm__ volatile("" ::: "memory");
    SCRSetRootScaleRatio(o->h, o->r);
    SCRSetCharaRootTurnScaleRatio(o->h, o->r);
}

static void func_0010F710(char *c, int mode)
{
    char *s = *(char **)(c + 0xCC);
    float a;
    float b;
    float d;

    switch (mode) {
    case 0:
        if (*(int *)(*(char **)(c + 0x14) + 0x750) != *(int *)(s + 0x20))
            return;
        CharaCtrlSetScriptCtrlStatus(*(int *)(c + 8), ScriptCtrlDef_SCRAccel->status);
        if (*(int *)(s + 0x30) != 0)
            CharaCtrlSetScriptCtrlStatus(*(int *)(c + 8), ScriptCtrlDef_SCRDash->status);
        return;
    case 2:
        a = *(float *)(c + 0x158);
        b = -a;
        d = adjustAnglePI(*(float *)(c + 0x1DC) - a);
        if (*(int *)(s + 0x9C) != 0 && fabsf(*(float *)(c + 0x158)) > 1.5707963f &&
            fabsf(d - b) >= 3.1415927f)
            a = *(float *)(c + 0x1DC);
        if (0.0f <= a)
            CharaCtrlSetScriptCtrlStatus(*(int *)(c + 8), ScriptCtrlDef_SCRStopR->status);
        else
            CharaCtrlSetScriptCtrlStatus(*(int *)(c + 8), ScriptCtrlDef_SCRStopL->status);
        return;
    case 1:
        if (0.0f <= *(float *)(c + 0x158))
            CharaCtrlSetScriptCtrlStatus(*(int *)(c + 8), ScriptCtrlDef_SCRFastR->status);
        else
            CharaCtrlSetScriptCtrlStatus(*(int *)(c + 8), ScriptCtrlDef_SCRFastL->status);
        return;
    case 3:
        CharaCtrlSetScriptCtrlStatus(*(int *)(c + 8), (*(ScriptCtrlDef * *)&ScriptCtrlDef_SCRStop)->status);
        return;
    case 4:
        CharaCtrlSetScriptCtrlStatus(*(int *)(c + 8), ScriptCtrlDef_SCRBack->status);
        return;
    case 5:
        CharaCtrlSetScriptCtrlStatus(*(int *)(c + 8), (*(ScriptCtrlDef * *)&ScriptCtrlDef_SCRStop)->status);
        return;
    case 6:
        if (0.0f <= *(float *)(c + 0x130)) {
            CharaCtrlSetScriptCtrlStatus(*(int *)(c + 8), ScriptCtrlDef_SCRTransR->status);
            return;
        } else
            CharaCtrlSetScriptCtrlStatus(*(int *)(c + 8), ScriptCtrlDef_SCRTransL->status);

    }
}

void setDashSlowLegCtrlWork(void *arg0, int arg1)
{
    (*(int *)((char *)(arg0) + 0x30)) = arg1;
}

void setStabilizeYSlowLegCtrlWork(void *arg0, int arg1)
{
    (*(int *)((char *)(arg0) + 0x3C)) = arg1;
}

void setMoveModeSlowLegCtrlWork(void *arg0, int arg1)
{
    (*(int *)((char *)(arg0) + 0x34)) = arg1;
}

void setMotScaleMaxSlowLegCtrlWork(void *arg0, float fparg0)
{
    (*(float *)((char *)(arg0) + 0x38)) = fparg0;
}

void setAttainMotScaleSlowLegCtrlWork(void *arg0, float fparg0)
{
    (*(float *)((char *)(arg0) + 0x40)) = fparg0;
}

void setGuardModeSlowLegCtrlWork(void *arg0, int arg1)
{
    (*(int *)((char *)(arg0) + 0x9C)) = arg1;
}

void deleteSlowLegCtrlWork(void)
{

}

static void func_0010FA18(int obj, char *w)
{
    _resetBaseMoveWork(obj, w);
    *(int *)(w + 0x30) = 0;
    *(float *)(w + 0x40) = 1.0f;
    *(int *)(w + 0x9C) = 0;
    *(int *)(w + 0x34) = 0;
    *(int *)(w + 0x74) = 0;
    *(int *)(w + 0x78) = 0;
    *(int *)(w + 0x3C) = 0;
    func_0010FA88(w);
    *(int *)(w + 0x98) = *(signed char *)(GetCharacterClass(obj) + 0x363);
}

static void func_0010FA88(char *p)
{
    *(int *)(p + 0x94) = 0;
}

static void func_0010FA90(char *p, u_long128 *target)
{
    Vec4_func_0010FA90 d;

    W(u_long128, 0x120) = *target;
    matApply(p + 0x130, p + 0x20, target);
    vecSub(p + 0x130, p + 0x130, p + 0x110);
    d.q = W(u_long128, 0x130);
    d.f[3] = 1.0f;
    d.f[1] = 0;
    W(float, 0x154) = vecLen(&d);
    vecNormalize1(&d);
    W(float, 0x158) = iosGetATan2fExact(d.f[0], d.f[2]);
}

static float func_0010FB70(char *a, float x)
{
    return calcAngleTime(x, *(float *)(a + 0xA8), *(float *)(a + 0xA4),
                         *(float *)(**(char ***)(a + 0x1C) + 0x78));
}

static void func_0010FB98(char *o, float *r, float f)
{
    struct {
        float out;
        s128 v;
    } t;
    char *c = *(char **)(o + 0xCC);
    char *m = *(char **)(o + 0x1C);

    PredictMotionGeometryPotentialWithScaleElem(&t.v, &t.out, *(int *)(o + 8), *(int *)m, *(float *)(m + 0xC), -1.0f);
    if ((0.0f <= t.out && 0.0f <= *r) || (t.out <= 0.0f && *r <= 0.0f)) {
        *(float *)(o + 0x160) = *(float *)(o + 0x154) / f;
    } else {
        *(float *)(o + 0x160) = *(float *)(c + 0x58);
    }
}
