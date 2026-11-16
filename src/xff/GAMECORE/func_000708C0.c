typedef struct {
    int pad0;
    void *obj;
} SightActor;

typedef struct {
    int normalFlag;
    int pad4;
    int hardFlag;
    int padC;
    int pad10;
} TimeAttackItem;

typedef struct {
    int pad0[3];
    int count;
    TimeAttackItem *items;
} TimeAttackItemList;

extern int ScriptCtrlDef_SCRHorseSightOnTurnNone;
extern int GAMEUTIL_is_player_obj(void *obj);
extern void *GAMEUTIL_get_riding_horse_object(void *obj);
extern void setHorseForceScriptKey(void *horse, int key);
extern void SCRRequestMotionDirect(void *obj, int key);
extern TimeAttackItemList SH_TimeAttackItemListDEFAULT;
extern int getGameHardMode(void);
extern void mcGetCompleteTimeAttack(int *normal, int *hard);
extern void mcSetCompleteTimeAttack(int normal, int hard);
extern int _omakeGetFlagChk(int flag);
extern int dispCompleteAlertNormal;
extern int dispCompleteAlertHard;

static void func_000708E0(SightActor *a, int playerKey, int horseKey);

static void func_000708C0(SightActor *a)
{
    func_000708E0(a, 0, ScriptCtrlDef_SCRHorseSightOnTurnNone);
}

static void func_000708E0(SightActor *a, int playerKey, int horseKey)
{
    void *horse;

    if (GAMEUTIL_is_player_obj(a->obj) == 1) {
        horse = GAMEUTIL_get_riding_horse_object(a->obj);
        if (horse) {
            setHorseForceScriptKey(horse, horseKey);
        } else {
            SCRRequestMotionDirect(a->obj, playerKey);
        }
    }
}

static void func_00070978(void)
{
    TimeAttackItemList *list = &SH_TimeAttackItemListDEFAULT;
    int count = list->count;
    TimeAttackItem *e = list->items;
    int i;
    int hard = getGameHardMode();
    int normalOk;
    int hardOk;
    int done[2];

    dispCompleteAlertNormal = dispCompleteAlertHard = 0;
    normalOk = hard == 0;
    hardOk = hard != 0;
    mcGetCompleteTimeAttack(&done[0], &done[1]);
    for (i = 0; i < count; i++) {
        if (hard == 0) {
            if (normalOk && e[i].normalFlag && !_omakeGetFlagChk(e[i].normalFlag)) {
                normalOk = 0;
            }
        } else {
            if (hardOk && e[i].hardFlag && !_omakeGetFlagChk(e[i].hardFlag)) {
                hardOk = 0;
            }
        }
    }
    if (done[0] == 0) {
        if (normalOk || hardOk) {
            dispCompleteAlertNormal = done[0] = 1;
        }
    } else if (done[1] == 0) {
        if (normalOk || hardOk) {
            dispCompleteAlertHard = done[1] = 1;
        }
    }
    mcSetCompleteTimeAttack(done[0], done[1]);
}
