typedef struct {
    char pad00[0x30];
    int x30;
    int x34;
    char pad38[0x18];
    float x50;
    char pad54[0x24];
    float x78;
    char pad7C[0x48];
    float xC4;
} MoveParam;

typedef struct {
    char pad000[0x5E4];
    int x5E4;
} CharaWork;

typedef struct {
    char pad00[4];
    int status;
} ScriptCtrlDef;

typedef struct {
    char pad000[8];
    void *ctrl;
    char pad00C[8];
    CharaWork *work;
    char pad018[0x94];
    float xAC;
    char pad0B0[0x14];
    int xC4;
    int xC8;
    MoveParam *param;
    char pad0D0[0x60];
    float x130;
    float x134;
    char pad138[4];
    float x13C;
    char pad140[8];
    int x148;
} Chara;

extern ScriptCtrlDef *ScriptCtrlDef_SCRAccel;
extern ScriptCtrlDef *ScriptCtrlDef_SCRBack;
extern ScriptCtrlDef *ScriptCtrlDef_SCRDash;
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
extern float fabsf(float);

static inline int canDash(Chara *c, int check)
{
    MoveParam *p = c->param;
    int r;

    if (p->x34 == 0) {
        r = 0;
    } else if (c->xC4 != 0 && p->x78 * 0.5f < fabsf(c->x130)) {
        r = 0;
    } else if (c->xC8 != 0 && c->x13C / p->xC4 < 1.0f && p->x78 * 0.5f < fabsf(c->x134)) {
        r = 0;
    } else {
        r = 1;
        if (check != 0 && p->x30 != 0 && !(c->x13C / p->xC4 > fabsf(c->x130) / p->x78))
            r = 0;
    }
    return r;
}

void func_00106C80(Chara *c, int check)
{
    MoveParam *p = c->param;

    if (c->x148 == 0) {
        CharaCtrlSetScriptCtrlStatus(c->ctrl, ScriptCtrlDef_SCRAccel->status);
        if (canDash(c, check)) {
            CharaCtrlSetScriptCtrlStatus(c->ctrl, ScriptCtrlDef_SCRDash->status);
        } else if (p->x50 < c->xAC) {
            c->work->x5E4 = 0;
        }
    } else {
        CharaCtrlSetScriptCtrlStatus(c->ctrl, ScriptCtrlDef_SCRBack->status);
    }
}
