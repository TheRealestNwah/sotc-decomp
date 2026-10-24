extern int GAMEUTIL_is_player_obj(void *);
extern char *GetCharacterClass(void *);
extern long getPlayerLastAttrStatus(void);
extern int ControlMode_PLAYER_SWIM_DASH;

static inline int isHitExceptUnderwater(void *actor)
{
    if (GAMEUTIL_is_player_obj(actor) == 1 &&
        *(int *)(GetCharacterClass(actor) + 0x750) == ControlMode_PLAYER_SWIM_DASH)
        return 0;
    return 1;
}

char NICO_is_hit_except_underwater_or_boss(void *actor)
{
    int hit = isHitExceptUnderwater(actor);
    int boss = 1;
    int result;

    if ((getPlayerLastAttrStatus() & 1) == 0)
        boss = 0;
    result = boss == 0;
    if (hit != 0)
        return result;
    return 0;
}
