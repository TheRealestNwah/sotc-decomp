extern void GAMEUTIL_reset_interp_ratio_cntrl(int *);
extern void func_000E1650(void *);
void CAM_reset_aim_angle_rot(void *object)
{
    func_000E1650(object);
    *(int *)((char *)object + 0x20) = 0;
    GAMEUTIL_reset_interp_ratio_cntrl((int *)((char *)object + 0x24));
}
