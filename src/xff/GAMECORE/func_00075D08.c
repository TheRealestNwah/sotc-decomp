typedef struct {
    char pad0[0x44];
    float rate;
    float limit;
} FaintParam;

typedef struct {
    char pad0[0x154];
    int count;
    float time;
    float lastX;
    float lastY;
    char pad164[0x184 - 0x164];
    FaintParam *param;
} FaintWork;

typedef struct {
    char pad0[8];
    unsigned int trig;
} PadData;

typedef struct {
    char pad0[0x750];
    int controlMode;
} CharaClass;

typedef struct {
    char pad0[4];
    int status;
} ScriptCtrlDef;

extern int ControlMode_PLAYER_FAINT;
extern ScriptCtrlDef *ScriptCtrlDef_SCRPlayerFaintLoop;
extern char gcGlobalVar[];
extern PadData padManagerData;
extern void *isysGetThisSubThread(void);
extern void GAMEUTIL_get_1p_left_analog_input(float *, float *);
extern CharaClass *GetCharacterClass(void *);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);

static void func_00075D08(FaintWork *w)
{
    float x, y;
    int *faint = &ControlMode_PLAYER_FAINT;
    void *thread = isysGetThisSubThread();
    PadData *pad;

    GAMEUTIL_get_1p_left_analog_input(&x, &y);
    if (*faint == GetCharacterClass(thread)->controlMode) {
        if (w->lastX * x <= 0.0f && __builtin_fabsf(x) > 0.7f) {
            w->lastX = x;
            w->count++;
            w->lastY = y;
        }
        if (w->lastY * y <= 0.0f && __builtin_fabsf(y) > 0.7f) {
            w->lastX = x;
            w->lastY = y;
            w->count++;
        }
        pad = &padManagerData;
        if (pad->trig & 0x40)
            w->count++;
        if (pad->trig & 0x10)
            w->count++;
        if (pad->trig & 0x80)
            w->count++;
        if (pad->trig & 0x20)
            w->count++;
        w->time += *(float *)(gcGlobalVar + 0x180);
        if (!(w->param->limit < w->time + (float)w->count * w->param->rate))
            CharaCtrlSetScriptCtrlStatus(thread, ScriptCtrlDef_SCRPlayerFaintLoop->status);
    } else {
        w->lastX = x;
        w->lastY = y;
        w->time = 0.0f;
        w->count = 0;
    }
}
