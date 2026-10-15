extern char *GetCharacterClass(void *);
extern int GAMEUTIL_is_player_obj(void *);
extern int ControlMode_PLAYER_SWIM, ControlMode_PLAYER_SWIM_MOVE, ControlMode_PLAYER_SWIM_DASH;

int GAMEUTIL_is_swimming_now(void *o)
{
    int m;
    if (GAMEUTIL_is_player_obj(o) == 1) {
        m = *(int *)(GetCharacterClass(o) + 0x750);
        if (m == ControlMode_PLAYER_SWIM || m == ControlMode_PLAYER_SWIM_MOVE || m == ControlMode_PLAYER_SWIM_DASH)
            return 1;
    }
    return 0;
}
