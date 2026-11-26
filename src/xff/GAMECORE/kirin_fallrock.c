extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void *GetSCRCharaAIWorkPtr(int);
extern int SCRGetFirstObj(void *);
extern unsigned char gcGlobalVar[];
extern char *getSCRDataCtrlWork(void *);

static void func_00062FD8(void);

void SCRKirinFallRockEnd(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00062FD8);
}

void SCRFuncSetFallRockTimerAndSetGroundDestFlag(void)
{
    float temp_f0;
    int temp_v0;
    void *temp_v0_2;

    temp_v0 = SCRGetFirstObj(gcGlobalVar + 0x2B8);
    if (temp_v0 != 0) {
        temp_v0_2 = GetSCRCharaAIWorkPtr(temp_v0);
        if ((*(int *)((char *)(temp_v0_2) + 0x41B8)) != 0) {
            temp_f0 = (*(float *)((char *)(temp_v0_2) + 0x41B4)) + 0.5f;
            (*(float *)((char *)(temp_v0_2) + 0x41B4)) = temp_f0;
            if (temp_f0 > 5.0f) {
                (*(float *)((char *)(temp_v0_2) + 0x41B4)) = 5.0f;
            }
            (*(int *)((char *)(temp_v0_2) + 0x41BC)) = 1;
        }
    }
}

void SCRFuncSetFallRockTimer(void)
{
    float temp_f0;
    int temp_v0;
    void *temp_v0_2;

    temp_v0 = SCRGetFirstObj(gcGlobalVar + 0x2B8);
    if (temp_v0 != 0) {
        temp_v0_2 = GetSCRCharaAIWorkPtr(temp_v0);
        if ((*(int *)((char *)(temp_v0_2) + 0x41B8)) != 0) {
            temp_f0 = (*(float *)((char *)(temp_v0_2) + 0x41B4)) + 0.5f;
            (*(float *)((char *)(temp_v0_2) + 0x41B4)) = temp_f0;
            if (temp_f0 > 5.0f) {
                (*(float *)((char *)(temp_v0_2) + 0x41B4)) = 5.0f;
            }
        }
    }
}

void SCRFuncKirinFallRockMain(void *actor)
{
    float temp_f0;
    float temp_f1;
    void *temp_v0;

    temp_v0 = GetSCRCharaAIWorkPtr(actor);
    temp_f1 = (*(float *)((char *)(temp_v0) + 0x41B4));
    if (temp_f1 > 0.0f) {
        temp_f0 = temp_f1 - (*(float *)((char *)(gcGlobalVar) + 0x180));
        (*(float *)((char *)(temp_v0) + 0x41B4)) = temp_f0;
        if (temp_f0 < 0.0f) {
            (*(float *)((char *)(temp_v0) + 0x41B4)) = 0.0f;
        }
    }
}

int SCRConditionFallRockChack(void *actor)
{
    char *w = GetSCRCharaAIWorkPtr(actor);
    int r = 1;
    if (!(0.0f < *(float *)(w + 0x41B4)))
        r = 0;
    return r;
}

void SCRFuncKirinFallRockTimerSetFlagOn(void *actor)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41B8)) = 1;
}

void SCRFuncKirinFallRockTimerSetFlagOff(void *actor)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41B8)) = 0;
}

int SCRConditionKirinIntervalOfMovement(void *actor, int n, int lim)
{
    return (int)*(float *)(getSCRDataCtrlWork(actor) + 0x40A4) % n < lim;
}

static void func_00062FD8(void)
{
    void *obj;
    char *w;

    obj = SCRGetFirstObj(((char *)&gcGlobalVar) + 0x2B8);
    if (obj != 0) {
        w = GetSCRCharaAIWorkPtr(obj);
        if (*(int *)(w + 0x41B0) > 0) {
            *(int *)(w + 0x41B0) -= 1;
        }
    }
}
