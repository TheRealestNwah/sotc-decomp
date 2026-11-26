extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void *GetSCRCharaAIWorkPtr(void *);
typedef struct {
    char p0[8];
    int id;
} GameObj;
extern GameObj *GameObject_KNIGHT_ARM_BREAK;
extern GameObj *GameObject_KNIGHT_ARM_PARTS;
extern GameObj *GameObject_KNIGHT_NECK_PARTS;
extern GameObj *GameObject_KNIGHT_NECK_BREAK;
extern int chkGameFlagForGameObj(int);
extern int setGameFlagForGameObj(int);
extern void _SCRStartLWS(int, int, int, int);

static void func_00063980(void *character);

void SCRKnightBossPartsDelete(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00063980);
}

void SCRFuncKnightSetStand(void *actor)
{
    void *temp_v0;

    temp_v0 = GetSCRCharaAIWorkPtr(actor);
    (*(int *)((char *)(temp_v0) + 0x41B0)) = (int) ((*(int *)((char *)(temp_v0) + 0x41B0)) | 1);
}

void SCRFuncKnightSetWalk(void *actor)
{
    int temp_v0_2;
    void *temp_v0;

    temp_v0 = GetSCRCharaAIWorkPtr(actor);
    temp_v0_2 = (*(int *)((char *)(temp_v0) + 0x41B0));
    if (!(temp_v0_2 & 4)) {
        (*(int *)((char *)(temp_v0) + 0x41B0)) = (int) (temp_v0_2 | 2);
    }
}

void SCRFuncKnightSetShakeStop(void *actor)
{
    int temp_v0_2;
    void *temp_v0;

    temp_v0 = GetSCRCharaAIWorkPtr(actor);
    temp_v0_2 = (*(int *)((char *)(temp_v0) + 0x41B0));
    if (!(temp_v0_2 & 4)) {
        (*(int *)((char *)(temp_v0) + 0x41B0)) = (int) (temp_v0_2 | 4);
    }
}

int SCRConditionKnightGetStandKeyFlag(void *actor)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41B0)) & 1;
}

static void func_00063980(void *character)
{
    if (chkGameFlagForGameObj(GameObject_KNIGHT_ARM_BREAK->id) == 0) {
        _SCRStartLWS(GameObject_KNIGHT_ARM_PARTS->id, -1, 1, 0);
        _SCRStartLWS(GameObject_KNIGHT_NECK_PARTS->id, -1, 1, 0);
        setGameFlagForGameObj(GameObject_KNIGHT_ARM_BREAK->id);
        setGameFlagForGameObj(GameObject_KNIGHT_NECK_BREAK->id);
    }
}
