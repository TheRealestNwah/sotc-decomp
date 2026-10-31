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

static void func_00063980(void *character)
{
    if (chkGameFlagForGameObj(GameObject_KNIGHT_ARM_BREAK->id) == 0) {
        _SCRStartLWS(GameObject_KNIGHT_ARM_PARTS->id, -1, 1, 0);
        _SCRStartLWS(GameObject_KNIGHT_NECK_PARTS->id, -1, 1, 0);
        setGameFlagForGameObj(GameObject_KNIGHT_ARM_BREAK->id);
        setGameFlagForGameObj(GameObject_KNIGHT_NECK_BREAK->id);
    }
}
