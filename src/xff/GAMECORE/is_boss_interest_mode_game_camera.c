extern int func_000EB958(void *);
extern int D_0017B730;
extern int D_0017B72C;
extern int GAMEUTIL_is_push_or_down_1p_button(int, int);
extern int *GetPlayerControlButtonContext(void);
extern int GAMEUTIL_get_boss_interest_position(float *, int);
extern void *CAM_get_target_obj(void *);
extern int CheckSwordIndicateAimPoint(void *);
static inline int is_push_interest_button(char *cam)
{
    if (GAMEUTIL_is_push_or_down_1p_button(0, D_0017B72C) == 1
        || (*(int *)(cam + 0x3110) == 1 && GAMEUTIL_is_push_or_down_1p_button(0, GetPlayerControlButtonContext()[5]) == 1))
        return 1;
    return 0;
}
int is_boss_interest_mode_game_camera(int mode, char *cam)
{
    char *w = cam + 0x1370;
    float pos[4];
    if (*(int *)(w + 4) == 1 && !func_000EB958(w) && !D_0017B730 && is_push_interest_button(cam) == 1) {
        if (mode == 4) return 1;
        if (GAMEUTIL_get_boss_interest_position(pos, 0) == 1 || CheckSwordIndicateAimPoint(CAM_get_target_obj(w + 0x23C)) > 0) return 1;
    }
    return 0;
}
