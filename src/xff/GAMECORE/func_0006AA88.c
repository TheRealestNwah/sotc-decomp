typedef struct {
    char pad0[8];
    int id;
} GameObject;

extern GameObject *GameObject_CANOSSA_WALL11;
extern GameObject *GameObject_CANOSSA_WALL16;
extern GameObject *GameObject_CANOSSA_WALL17;
extern int setGameFlagForGameObj(int);

static int func_0006AA88(void)
{
    setGameFlagForGameObj(GameObject_CANOSSA_WALL11->id);
    setGameFlagForGameObj(GameObject_CANOSSA_WALL16->id);
    return setGameFlagForGameObj(GameObject_CANOSSA_WALL17->id);
}
