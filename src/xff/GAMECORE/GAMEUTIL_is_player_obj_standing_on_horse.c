extern char *GetCharacterClass(void *);

static inline int get_character_type(void *actor)
{
    char *c;
    if (actor != 0) {
        c = GetCharacterClass(actor);
        if (c != 0)
            return *(short *)(c + 0x370);
    }
    return -1000000;
}

extern int ControlMode_PLAYER_RIDING_STAND;
extern int ControlMode_PLAYER_RIDING_STAND_END;
extern int ControlMode_PLAYER_RIDINGSTAND_WEAPON;
extern int ControlMode_PLAYER_RIDING_STD_BOW;
extern int ControlMode_PLAYER_RIDING_STD_BOW_NO_SYNC;
extern int ControlMode_PLAYER_RIDING_STD_BOW_CANCEL;

static inline int is_player_obj(void *actor)
{
    return get_character_type(actor) == 2;
}

int GAMEUTIL_is_player_obj_standing_on_horse(void *actor)
{
    if (is_player_obj(actor)) {
        int mode = *(int *)(GetCharacterClass(actor) + 0x750);

        if (mode == ControlMode_PLAYER_RIDING_STAND || mode == ControlMode_PLAYER_RIDING_STAND_END
            || mode == ControlMode_PLAYER_RIDINGSTAND_WEAPON || mode == ControlMode_PLAYER_RIDING_STD_BOW
            || mode == ControlMode_PLAYER_RIDING_STD_BOW_NO_SYNC || mode == ControlMode_PLAYER_RIDING_STD_BOW_CANCEL)
            return 1;
    }
    return 0;
}
