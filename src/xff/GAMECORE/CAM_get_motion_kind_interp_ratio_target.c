extern float GAMEUTIL_get_interp_ratio_interp_ratio_cntrl(void *);
float CAM_get_motion_kind_interp_ratio_target(char *object)
{
    return GAMEUTIL_get_interp_ratio_interp_ratio_cntrl(object + 8);
}
