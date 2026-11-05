typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    char pad0[0x180];
    Vec4 rot;
    char pad190[0x19C - 0x190];
    int dir;
    int motion;
    float turn;
    char pad1A8[0x204 - 0x1A8];
    float speed;
} Actor;

extern void *isysGetThisSubThread(void);
extern int *ScriptCtrlDef_SCRGoR;
extern int *ScriptCtrlDef_SCRGoL;
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
extern void SCRCharaTurnDirectInput(void *, float);

static inline void quatRotate(float *out, float *q, float *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%1)\n"
                         "vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%0)\n"
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
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf0, vf8w\n"
                         : : "r"(q), "r"(v));
    __asm__ __volatile__("sqc2 vf10, 0x0(%0)\n" : : "r"(out) : "memory");
}

static void func_000B0160(Actor *a, float *pos, int mode, float k)
{
    void *th = isysGetThisSubThread();
    Vec4 d;

    quatRotate(d.f, a->rot.f, pos);
    if (mode == 12) {
        if (0.0f < d.f[0]) {
            a->dir = 6;
            a->speed = -k * a->turn;
        } else {
            a->dir = 7;
            a->speed = k * a->turn;
        }
    } else {
        if (d.f[0] < 0.0f) {
            a->dir = 6;
            a->speed = -k * a->turn;
        } else {
            a->dir = 7;
            a->speed = k * a->turn;
        }
    }
    if (a->speed < 0.0f ? -0.5f < a->speed : a->speed < 0.5f) {
        if (a->speed < 0.0f)
            CharaCtrlSetScriptCtrlStatus(th, ScriptCtrlDef_SCRGoL[1]);
        else
            CharaCtrlSetScriptCtrlStatus(th, ScriptCtrlDef_SCRGoR[1]);
        SCRCharaTurnDirectInput(th, a->speed);
    } else {
        if (a->speed < 0.0f)
            a->motion = 0x2C;
        else
            a->motion = 0x2D;
    }
}
