extern char *GetCharacterClass(void *);
extern int ControlMode_PLAYER_RIDING_HANG, ControlMode_PLAYER_RIDING_HANG_DOWN_R;
extern int ControlMode_PLAYER_RIDING_HANG_DOWN_L, ControlMode_PLAYER_DUMMY;

int player_IsHorseHang(void *o)
{
    int m = *(int *)(GetCharacterClass(o) + 0x750);
    if (m == ControlMode_PLAYER_RIDING_HANG || m == ControlMode_PLAYER_RIDING_HANG_DOWN_R ||
        m == ControlMode_PLAYER_RIDING_HANG_DOWN_L || m == ControlMode_PLAYER_DUMMY)
        return 1;
    return 0;
}
