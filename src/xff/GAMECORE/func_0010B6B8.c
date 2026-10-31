typedef struct { int pad0; int id; } ScriptCtrlDef;
typedef struct { char pad0[0x30]; int dash; } PadInfo;
typedef struct {
    char pad0[8];
    void *chara;
    char padC[0xCC - 0xC];
    PadInfo *pad;
} Ctrl;

extern ScriptCtrlDef *ScriptCtrlDef_SCRAccel;
extern ScriptCtrlDef *ScriptCtrlDef_SCRDash;
extern void CharaCtrlSetScriptCtrlStatus(void *, int);

static void func_0010B6B8(Ctrl *c)
{
    CharaCtrlSetScriptCtrlStatus(c->chara, ScriptCtrlDef_SCRAccel->id);
    if (c->pad->dash)
        CharaCtrlSetScriptCtrlStatus(c->chara, ScriptCtrlDef_SCRDash->id);
}
