typedef struct {
    char pad0[0x12C];
    float timer;
    float limit;
    char pad134[0x19C - 0x134];
    int dir;
    int motion;
    float turn;
    char pad1A8[0x204 - 0x1A8];
    float speed;
} Actor;

extern void *isysGetThisSubThread(void);
extern float iosGetRandom(void);
extern int *ScriptCtrlDef_SCRGoR;
extern int *ScriptCtrlDef_SCRGoL;
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
extern void SCRCharaTurnDirectInput(void *, float);

static inline void turnLeft(Actor *a, void *th)
{
    a->speed = a->turn * -0.25f;
    CharaCtrlSetScriptCtrlStatus(th, ScriptCtrlDef_SCRGoL[1]);
    SCRCharaTurnDirectInput(th, a->speed);
}

static inline void turnRight(Actor *a, void *th)
{
    a->speed = a->turn * 0.25f;
    CharaCtrlSetScriptCtrlStatus(th, ScriptCtrlDef_SCRGoR[1]);
    SCRCharaTurnDirectInput(th, a->speed);
}

static void func_000B0E28(Actor *a)
{
    void *th = isysGetThisSubThread();
    float t = iosGetRandom() + 1.0f;
    float r = iosGetRandom();

    if (a->timer < a->limit) {
        if (r < 0.2f)
            a->dir = 6;
        else if (r < 0.4f)
            a->dir = 7;
        else
            a->dir = 5;
        a->timer = t;
        a->limit = 0.0f;
    }
    a->motion = 0x29;
    switch (a->dir) {
    case 5:
        a->speed = 0.0f;
        break;
    case 7:
        turnRight(a, th);
        break;
    case 6:
        turnLeft(a, th);
        break;
    }
}
