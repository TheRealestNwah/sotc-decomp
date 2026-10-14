extern int GAMEUTIL_get_interp_ratio_interp_ratio_cntrl();

int CAM_get_motion_kind_interp_ratio_target(int a, int b, int c, int d)
{
    return GAMEUTIL_get_interp_ratio_interp_ratio_cntrl(a + 8, b, c, d);
}
