extern void GAMEUTIL_constructor_position_filter(char *);
extern void GAMEUTIL_reset_status_manager(char *, int);
extern void GAMEUTIL_reset_collision_info(char *);
extern void GAMEUTIL_constructor_interp_ratio_cntrl(char *);
extern void GAMEUTIL_set_param_interp_ratio_cntrl(char *, float, float);
extern void GAMEUTIL_forward_timer_still_one_ratio_time_interp_ratio_cntrl(char *);

void CAM_constructor_target_visibility(char *c)
{
    GAMEUTIL_constructor_position_filter(c);
    *(int *)(c + 0x30) = 0;
    GAMEUTIL_reset_status_manager(c + 0x34, 0);
    *(int *)(c + 0x44) = 0;
    GAMEUTIL_reset_collision_info(c + 0x50);
    GAMEUTIL_reset_collision_info(c + 0xB0);
    GAMEUTIL_constructor_interp_ratio_cntrl(c + 0x110);
    GAMEUTIL_set_param_interp_ratio_cntrl(c + 0x110, 0.0f, 1.5f);
    GAMEUTIL_forward_timer_still_one_ratio_time_interp_ratio_cntrl(c + 0x110);
    *(int *)(c + 0x130) = 0;
}
