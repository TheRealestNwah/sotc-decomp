extern void GAMEUTIL_reset_interp_ratio_cntrl(int);
extern void func_000E1650();

void CAM_reset_aim_angle_rot(void *arg0)
{
    func_000E1650();
    (*(int *)((char *)(arg0) + 0x20)) = 0;
    GAMEUTIL_reset_interp_ratio_cntrl(arg0 + 0x24);
}
