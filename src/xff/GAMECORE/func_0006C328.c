/* func_0006C328: projectile thread for the BUDDHA/TTS/PSD/YAMORI shots: sets up the shot LWS, homes the type-2 shot toward the player, moves it by the frame time, clips against the player and the world, then plays the hit LWS and sends the buddha explode damage. The lws argument of GetScriptAnimationGlobalBaseInfo is pinned to $a0 behind an empty asm so reorg fills the collision-result branch with the $a0 move as a plain bnez, as in the Original. The 4.3f store goes through an int/float union so gcc keeps the info+8 load after it. */
typedef int s128 __attribute__((mode(TI)));

typedef struct {
    char p0[0x180];
    float frameTime;
    char p184[0x2B0 - 0x184];
    int list[3];
} GcGlobal;
extern GcGlobal gcGlobalVar;
#define GC ((char *)&gcGlobalVar)
extern int ZeroPoint[];
extern int IdentityQuaternion[];
extern int RotX90Quaternion[];
extern int YUnitVector[];
extern int D_0017AD34;
extern int D_0017AD38;
extern int DamageDef_BUDDHA_EXPLODE_IMPACT;
extern int ScriptAnimationObjDef_BUDDHA_EXPLODE_NO_DAMAGE;
extern int ScriptAnimationObjDef_BUDDHA_SHOOT;
extern int ScriptAnimationObjDef_PSD_PLS_HIT;
extern int ScriptAnimationObjDef_PSD_PLS_HIT_GROUND;
extern int ScriptAnimationObjDef_PSD_PLS_HIT_PILLAR;
extern int ScriptAnimationObjDef_PSD_PLS_HIT_WATER;
extern int ScriptAnimationObjDef_PSD_PLS_SHOOT;
extern int ScriptAnimationObjDef_TTS_PLS_HIT;
extern int ScriptAnimationObjDef_TTS_PLS_HIT_GROUND;
extern int ScriptAnimationObjDef_TTS_PLS_HIT_WATER;
extern int ScriptAnimationObjDef_TTS_PLS_SHOOT;
extern int ScriptAnimationObjDef_YAMORI_B_BREATH_BALL;
extern int ScriptAnimationObjDef_YAMORI_B_BREATH_HIT;

extern int isysGetThisSubThread(void);
extern char *GetLayoutClass(int);
extern void isysJumpSubThread(void *, void *);
extern int SCRGetFirstObj(void *);
extern int _SCRSetupLWS(int, void *, void *, void *, int);
extern void _SCRStartLWS(int, int, int, int);
extern void UpdateLayoutClassPastGeometry(char *);
extern void UpdateLayoutClassGeometry(char *);
extern int nico_returnPlayerRidingFlag(int);
extern int ClipCollisionDirectCallBack(void *, void *, void *, void *, int (*)(), int, int, int (*)(), int);
extern int GetGeometryPointerObject(void *);
extern char *GetCharacterClass(int);
extern void isysRequestDeleteObj(int);
extern void ConvertGeometryPointerZNormalMode(void *, void *);
extern void GetGeometryPointerQuaternion(void *, void *);
extern void GetGeometryPointerPosition(void *, void *);
extern void DivQuaternion(void *, void *, void *);
extern long nico_GetGeometryPointerAttr(void *);
extern int getPlayerLastAttrStatus(void);
extern float *GetGeometryPointerSurfacePlane(void *);
extern int SCRGetCollisionCallBack(void *, void *, void *, void *, int (*)(), int);
extern char *GetScriptAnimationGlobalBaseInfo(int);
extern void SendDamageLetter(int, int, int, void *);
extern void GetQuaternionByAxisDirZY(void *, void *, void *);
extern void SCRSetLWSGeometry(int, int, void *, void *);
extern void scrRunM(int);
extern int func_0006D2E8();
extern int func_0006D2A0();
extern int func_0006D180();
extern int func_0006D1B0();

static inline float lenXYZ(void *a)
{
    float d;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a) : "$2");
    return d;
}

static inline float distXZ2(void *a, void *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2 $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static inline float distXYZ2(void *a, void *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2 $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static inline void sub4(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void add4(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void sub3(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void add3(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void scale3(void *out, void *a, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2 %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(s) : "memory");
}

static inline void scale4(void *out, void *a, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2 %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(s) : "memory");
}

static inline void normalize3(void *out, void *in)
{
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         ".set reorder\n"
                         : : "r"(out), "r"(in) : "memory");
}

#define V(p, o) (*(char **)((char *)(p) + (o)))

static void func_0006C328(int *arg0)
{
    struct {
        float v10[4];
        float v20[4];
        float v30[4];
        char geo[0x40];
        float v80[4];
        float v90[4];
        char col[0x40];
        float vE0[4];
        float vF0[4];
    } L __attribute__((aligned(16)));
    int self;
    int hitPlayer;
    int hit;
    char *pl;
    register char *s4 asm("s4");
    float *vel;
    float t;
    int lws;

    lws = 0;
    self = isysGetThisSubThread();
    s4 = GetLayoutClass(self);
    t = 0.0f;
    GetLayoutClass(self);
    if (arg0[4] == -1)
        isysJumpSubThread(func_0006D2E8, arg0);
    switch (arg0[4]) {
    case 2:
    case 3:
        lws = _SCRSetupLWS(ScriptAnimationObjDef_BUDDHA_SHOOT, 0, ZeroPoint, IdentityQuaternion, SCRGetFirstObj(GC + 0x2B8));
        break;
    case 0:
        lws = _SCRSetupLWS(ScriptAnimationObjDef_TTS_PLS_SHOOT, 0, ZeroPoint, IdentityQuaternion, SCRGetFirstObj(GC + 0x2B8));
        break;
    case 1:
        lws = _SCRSetupLWS(ScriptAnimationObjDef_PSD_PLS_SHOOT, 0, ZeroPoint, IdentityQuaternion, SCRGetFirstObj(GC + 0x2B8));
        break;
    case 4:
        lws = _SCRSetupLWS(ScriptAnimationObjDef_YAMORI_B_BREATH_BALL, 0, ZeroPoint, IdentityQuaternion, SCRGetFirstObj(GC + 0x2B8));
        break;
    }
    if (lws != 0)
        _SCRStartLWS(lws, -1, 4, 0);
    vel = (float *)(s4 + 0x30);
    for (;;) {
        UpdateLayoutClassPastGeometry(s4);
        if (arg0[4] == 2) {
            int o1 = SCRGetFirstObj(GC + 0x2B0);
            int o0 = SCRGetFirstObj(GC + 0x2B8);
            if (o1 != 0 && o0 != 0) {
                char *l1 = GetLayoutClass(o1);
                char *l0 = GetLayoutClass(o0);
                float len = lenXYZ(vel);
                float k = 3.0f;
                if (((float *)V(l1, 0x134))[1] < ((float *)V(s4, 0x134))[1]
                    && distXZ2(V(l0, 0x134), V(l1, 0x134)) > distXZ2(V(l0, 0x134), V(s4, 0x134))
                    && distXYZ2(V(l1, 0x134), V(s4, 0x134)) > 25.0f) {
                    sub4(L.v20, V(l0, 0x134), V(l1, 0x134));
                    L.v20[1] = 0.0f;
                    normalize3(L.v20, L.v20);
                    scale3(L.v20, L.v20, k);
                    add3(L.v30, V(l1, 0x134), L.v20);
                    sub3(vel, L.v30, V(s4, 0x134));
                    normalize3(vel, vel);
                    scale3(vel, vel, len);
                    *(float *)(s4 + 0x3C) = 1.0f;
                }
            }
        }
        scale3(L.v20, vel, gcGlobalVar.frameTime);
        add3(V(s4, 0x134), V(s4, 0x138), L.v20);
        hitPlayer = 0;
        hit = 0;
        {
            int o = SCRGetFirstObj(GC + 0x2B0);
            if (nico_returnPlayerRidingFlag(SCRGetFirstObj(GC + 0x2B0)))
                o = SCRGetFirstObj(GC + 0x2B4);
            pl = GetLayoutClass(o);
        }
        if ((unsigned)arg0[4] < 2) {
            if (ClipCollisionDirectCallBack(L.geo, V(s4, 0x138), V(s4, 0x134), GC + 0x240, 0, 0, 0, func_0006D2A0, 0)) {
                hit = 1;
                if (SCRGetFirstObj(GC + 0x2B0) == GetGeometryPointerObject(L.geo)
                    || SCRGetFirstObj(GC + 0x2B4) == GetGeometryPointerObject(L.geo))
                    hitPlayer = 1;
                if (*(int *)(GetCharacterClass(SCRGetFirstObj(GC + 0x2B8)) + 0x5B4) == GetGeometryPointerObject(L.geo)) {
                    isysRequestDeleteObj(lws);
                    switch (arg0[4]) {
                    case 0:
                        lws = _SCRSetupLWS(ScriptAnimationObjDef_TTS_PLS_HIT, L.geo, ZeroPoint, IdentityQuaternion, SCRGetFirstObj(GC + 0x2B8));
                        break;
                    case 1:
                        lws = _SCRSetupLWS(ScriptAnimationObjDef_PSD_PLS_HIT, L.geo, ZeroPoint, IdentityQuaternion, SCRGetFirstObj(GC + 0x2B8));
                        break;
                    }
                    _SCRStartLWS(lws, -1, 3, 0);
                    isysJumpSubThread(func_0006D2E8, arg0);
                }
            }
        } else if (arg0[4] == 4) {
            if (ClipCollisionDirectCallBack(L.geo, V(s4, 0x138), V(s4, 0x134), GC + 0x240, 0, 0, 0, func_0006D2A0, 0)) {
                hit = 1;
                if (SCRGetFirstObj(GC + 0x2B0) == GetGeometryPointerObject(L.geo)
                    || SCRGetFirstObj(GC + 0x2B4) == GetGeometryPointerObject(L.geo))
                    hitPlayer = 1;
            }
        } else {
            D_0017AD34 = SCRGetFirstObj(GC + 0x2B0);
            D_0017AD38 = SCRGetFirstObj(GC + 0x2B4);
            hit = ClipCollisionDirectCallBack(L.geo, V(s4, 0x138), V(s4, 0x134), GC + 0x240, func_0006D180, 0, 0, func_0006D2A0, 0) != 0;
        }
        if (hitPlayer) {
            isysRequestDeleteObj(lws);
            switch (arg0[4]) {
            case 0:
                lws = _SCRSetupLWS(ScriptAnimationObjDef_TTS_PLS_HIT, 0, V(pl, 0x134), IdentityQuaternion, SCRGetFirstObj(GC + 0x2B8));
                break;
            case 1:
                lws = _SCRSetupLWS(ScriptAnimationObjDef_PSD_PLS_HIT, 0, V(pl, 0x134), IdentityQuaternion, SCRGetFirstObj(GC + 0x2B8));
                break;
            case 4:
                sub3(L.v20, V(s4, 0x134), V(s4, 0x138));
                L.v20[1] = 0.0f;
                normalize3(L.v20, L.v20);
                L.v20[3] = 1.0f;
                GetQuaternionByAxisDirZY(L.v30, L.v20, YUnitVector);
                lws = _SCRSetupLWS(ScriptAnimationObjDef_YAMORI_B_BREATH_HIT, 0, V(pl, 0x134), L.v30, SCRGetFirstObj(GC + 0x2B8));
                break;
            }
            _SCRStartLWS(lws, -1, 3, 0);
            isysJumpSubThread(func_0006D2E8, arg0);
        } else if (hit) {
            ConvertGeometryPointerZNormalMode(L.geo, L.geo);
            GetGeometryPointerQuaternion(L.v30, L.geo);
            GetGeometryPointerPosition(L.v90, L.geo);
            DivQuaternion(L.v20, arg0, L.v30);
            isysRequestDeleteObj(lws);
            switch (arg0[4]) {
            case 0:
                if ((nico_GetGeometryPointerAttr(L.geo) & 0x7C00) == 0x3C00)
                    lws = _SCRSetupLWS(ScriptAnimationObjDef_TTS_PLS_HIT_WATER, L.geo, ZeroPoint, RotX90Quaternion, SCRGetFirstObj(GC + 0x2B8));
                else
                    lws = _SCRSetupLWS(ScriptAnimationObjDef_TTS_PLS_HIT_GROUND, L.geo, ZeroPoint, RotX90Quaternion, SCRGetFirstObj(GC + 0x2B8));
                break;
            case 1: {
                int attr = nico_GetGeometryPointerAttr(L.geo) & 0x7C00;
                if (attr == 0x3C00)
                    lws = _SCRSetupLWS(ScriptAnimationObjDef_PSD_PLS_HIT_WATER, L.geo, ZeroPoint, RotX90Quaternion, SCRGetFirstObj(GC + 0x2B8));
                else if (attr == 0x400)
                    lws = _SCRSetupLWS(ScriptAnimationObjDef_PSD_PLS_HIT_PILLAR, L.geo, ZeroPoint, RotX90Quaternion, SCRGetFirstObj(GC + 0x2B8));
                else
                    lws = _SCRSetupLWS(ScriptAnimationObjDef_PSD_PLS_HIT_GROUND, L.geo, ZeroPoint, RotX90Quaternion, SCRGetFirstObj(GC + 0x2B8));
                break;
            }
            case 2:
            case 3:
                lws = _SCRSetupLWS(ScriptAnimationObjDef_BUDDHA_EXPLODE_NO_DAMAGE, L.geo, ZeroPoint, RotX90Quaternion, SCRGetFirstObj(GC + 0x2B8));
                if ((getPlayerLastAttrStatus() & 0x1E00000) != 0x1A00000) {
                    int o0 = SCRGetFirstObj(GC + 0x2B0);
                    int o1 = SCRGetFirstObj(GC + 0x2B8);
                    if (o0 != 0 && o1 != 0) {
                        char *l0 = GetLayoutClass(o0);
                        char *l1 = GetLayoutClass(o1);
                        scale4(L.vE0, GetGeometryPointerSurfacePlane(L.geo), 0.0499999985f);
                        add4(L.vE0, L.vE0, L.v80);
                        if (distXYZ2(V(l0, 0x134), L.v80) <= 18.489996f
                            && SCRGetCollisionCallBack(L.col, L.vE0, V(l0, 0x134), GC + 0x230, func_0006D1B0, 0) == 0) {
                            char *info; { register int a asm("$4") = lws; __asm__ __volatile__("" : : "r"(a)); info = GetScriptAnimationGlobalBaseInfo(a); }
                            sub4(L.vF0, V(l1, 0x134), V(l0, 0x134));
                            L.vF0[1] = 0.0f;
                            normalize3(L.vF0, L.vF0);
                            scale4(L.vF0, L.vF0, 0.5f);
                            add4(L.vF0, L.vF0, V(l0, 0x134));
                            ((union { int i; float f; } *)&L.vF0[3])->f = 4.2999997138977051f;
                            SendDamageLetter(0, *(int *)(info + 8), DamageDef_BUDDHA_EXPLODE_IMPACT, L.vF0);
                        }
                    }
                }
                break;
            case 4:
                lws = _SCRSetupLWS(ScriptAnimationObjDef_YAMORI_B_BREATH_HIT, L.geo, ZeroPoint, L.v20, SCRGetFirstObj(GC + 0x2B8));
                break;
            }
            _SCRStartLWS(lws, -1, 3, 0);
            isysJumpSubThread(func_0006D2E8, arg0);
        }
        normalize3(L.v10, vel);
        GetQuaternionByAxisDirZY(arg0, L.v10, YUnitVector);
        if (lws != 0)
            SCRSetLWSGeometry(lws, 0, V(s4, 0x134), arg0);
        {
            char *me = GetLayoutClass(self);
            normalize3(L.v20, me + 0x30);
            GetQuaternionByAxisDirZY(V(me, 0x13C), L.v20, YUnitVector);
        }
        UpdateLayoutClassGeometry(s4);
        t += gcGlobalVar.frameTime;
        if (t > 20.0f)
            isysRequestDeleteObj(self);
        scrRunM(1);
    }
}
