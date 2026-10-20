extern void GAMEUTIL_set_param_extend_interp_ratio_cntrl(void *, float, float, float);

void CAM_set_interp_param_extend_aim_rot_common(char *p, float a, float b, float c)
{
    if (*(int *)(p + 0x20) == 0) {
        GAMEUTIL_set_param_extend_interp_ratio_cntrl(p + 0x24, a, b, c);
    }
}
