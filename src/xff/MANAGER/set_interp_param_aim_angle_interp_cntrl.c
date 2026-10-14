void set_interp_param_aim_angle_interp_cntrl(char *p, float f1, float f2)
{
    *(float *)(p + 0x4) = f1;
    *(float *)(p + 0x8) = f2;
}
