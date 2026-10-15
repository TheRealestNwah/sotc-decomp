extern int GAMEUTIL_is_player_obj(void *);
extern char *GetCharacterClass(void *);
extern int ControlMode_PLAYER_SWIM_DASH;

int NICO_is_hit_except_underwater(void *actor)
{
    if (GAMEUTIL_is_player_obj(actor) == 1 &&
        *(int *)(GetCharacterClass(actor) + 0x750) == ControlMode_PLAYER_SWIM_DASH)
        return 0;
    return 1;
}
