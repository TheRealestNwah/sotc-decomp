extern int GAMEUTIL_check_parent_flag();
extern int GAMEUTIL_is_player_obj(int);
extern void *GetCharacterClass(int);
extern int ControlMode_PLAYER_SWIM;
extern int ControlMode_PLAYER_SWIM_DASH;
extern int ControlMode_PLAYER_SWIM_MOVE;

int GAMEUTIL_is_floating_now(int arg0)
{
    int temp_a0;
    int var_a1;
    int var_v0;

    if (GAMEUTIL_check_parent_flag() == 0) {
        if ((GAMEUTIL_is_player_obj(arg0) != 1) || ((temp_a0 = (*(int *)((char *)(GetCharacterClass(arg0)) + 0x750)), var_a1 = 1, (temp_a0 != ControlMode_PLAYER_SWIM)) && (temp_a0 != ControlMode_PLAYER_SWIM_MOVE) && (temp_a0 != ControlMode_PLAYER_SWIM_DASH))) {
            var_a1 = 0;
        }
        var_v0 = 1;
        if (var_a1 != 0) {
            goto block_7;
        }
    } else {
block_7:
        var_v0 = 0;
    }
    return var_v0;
}
