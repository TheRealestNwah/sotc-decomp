typedef struct {
    char pad0[0x750];
    int controlMode;
} CharacterClass;

extern CharacterClass *GetCharacterClass(void);
extern long nico_GetGeometryPointerAttr(void *geometry);
extern int ControlMode_PLAYER_GRIP1;
extern int ControlMode_PLAYER_GRIP1_ATTACK;
extern int ControlMode_PLAYER_GRIP1_ATTACK2;
extern int ControlMode_PLAYER_GRIP2;
extern int ControlMode_PLAYER_GRIP2_ATTACK;
extern int ControlMode_PLAYER_GRIP2_ATTACK2;
extern int ControlMode_PLAYER_GRIP2_Y_REVISE_START;
extern int ControlMode_PLAYER_GRIP2_Y_REVISE;

static inline int isAttr(void *g, int mask)
{
    return (nico_GetGeometryPointerAttr(g) & mask) != 0;
}

static inline int attrA(void *g)
{
    return isAttr(g, 4);
}

static inline int attrB(void *g)
{
    return nico_GetGeometryPointerAttr(g) & 1;
}

static inline int attrC(void *g)
{
    return !isAttr(g, 2);
}

static inline int isTrue(long v)
{
    return v != 0;
}

static int func_0007BE98(void *self, void *g)
{
    int mode = GetCharacterClass()->controlMode;

    if (mode == ControlMode_PLAYER_GRIP1 || mode == ControlMode_PLAYER_GRIP1_ATTACK || mode == ControlMode_PLAYER_GRIP1_ATTACK2
        || mode == ControlMode_PLAYER_GRIP2 || mode == ControlMode_PLAYER_GRIP2_ATTACK
        || mode == ControlMode_PLAYER_GRIP2_ATTACK2 || mode == ControlMode_PLAYER_GRIP2_Y_REVISE_START
        || mode == ControlMode_PLAYER_GRIP2_Y_REVISE) {
        if (isTrue(attrA(g)) || (isTrue(attrB(g)) && isTrue(attrC(g))))
            return 1;
        return 0;
    }
    return 1;
}
