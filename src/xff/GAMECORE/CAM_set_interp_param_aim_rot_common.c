extern void GAMEUTIL_set_param_interp_ratio_cntrl(char *, float, float);

void CAM_set_interp_param_aim_rot_common(char *p, float start, float duration)
{
    if (*(int *)(p + 0x20) == 0) {
        GAMEUTIL_set_param_interp_ratio_cntrl(p + 0x24, start, duration);
    }
}
