typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    int valid;
    char pad4[0x10 - 4];
    char geo[0x60 - 0x10];
    int grip;
    char pad64[0x70 - 0x64];
    char edge[0xB0 - 0x70];
    char hand[0x60];
} GripWork;

extern char gcGlobalVar[];
extern int *SkelFocusDef_PLAYER_HAND_SUB_START;
extern int *ScriptCtrlDef_SCRPlayerEdgeGripSub;
extern int *ScriptCtrlDef_SCRPlayerHandGripSub;
extern char *GetCharacterClass(void *);
extern void GetCharacterClassMotionInterpNodePosition(float *, char *, int);
extern void GetGeometryPointerPosition(float *, void *);
extern int SCRGetCollisionCallBack(char *, float *, float *, void *, int (*)(), int);
extern int func_00091AB8();
extern int func_00090408(char *, char *, int);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
extern void CopyGeometryPointer(void *, void *);

static inline void vecScale(float *out, float *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}

static inline void vecAdd(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static void func_00090F28(void *obj, GripWork *w, int unused, float *dir)
{
    Vec4 hand;
    Vec4 end;
    Vec4 pos;
    Vec4 ofs;
    char geo[0x40];
    char *ch = GetCharacterClass(obj);

    GetCharacterClassMotionInterpNodePosition(hand.f, ch, SkelFocusDef_PLAYER_HAND_SUB_START[2]);
    if (w->valid != 0) {
        GetGeometryPointerPosition(pos.f, w->geo);
        if (pos.f[1] - 0.1f < hand.f[1])
            return;
    }
    vecScale(ofs.f, dir, 1.3f);
    vecAdd(end.f, hand.f, ofs.f);
    if (!SCRGetCollisionCallBack(geo, hand.f, end.f, gcGlobalVar + 0x230, func_00091AB8, 0))
        return;
    switch (func_00090408(geo, ch, 1)) {
    case 4:
        CharaCtrlSetScriptCtrlStatus(obj, ScriptCtrlDef_SCRPlayerEdgeGripSub[1]);
        w->grip |= 1;
        CopyGeometryPointer(w->edge, geo);
        break;
    case 2:
        CharaCtrlSetScriptCtrlStatus(obj, ScriptCtrlDef_SCRPlayerHandGripSub[1]);
        w->grip |= 2;
        CopyGeometryPointer(w->hand, geo);
        break;
    }
}
