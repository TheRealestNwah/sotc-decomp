extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern char gcGlobalVar[];
extern void *SCRGetFirstObj(void *);
extern char *GetSCRCharaAIWorkPtr(void *);
typedef struct {
    char pad0[8];
    int id;
} GameObject;
extern GameObject *GameObject_CANOSSA_WALL11;
extern GameObject *GameObject_CANOSSA_WALL16;
extern GameObject *GameObject_CANOSSA_WALL17;
extern int setGameFlagForGameObj(int);

static void func_0006AA40(void);
static int func_0006AA88(void);

void SCRCanossaWallBreakEnd(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_0006AA40);
}

void SCRCanossaWallDelete(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_0006AA88);
}

static void func_0006AA40(void)
{
    void *obj = SCRGetFirstObj(gcGlobalVar + 0x2B8);
    char *work;

    if (obj != 0) {
        work = GetSCRCharaAIWorkPtr(obj);
        if (*(int *)(work + 0x41E0) > 0) {
            *(int *)(work + 0x41E0) -= 1;
        }
    }
}

static int func_0006AA88(void)
{
    setGameFlagForGameObj(GameObject_CANOSSA_WALL11->id);
    setGameFlagForGameObj(GameObject_CANOSSA_WALL16->id);
    return setGameFlagForGameObj(GameObject_CANOSSA_WALL17->id);
}
