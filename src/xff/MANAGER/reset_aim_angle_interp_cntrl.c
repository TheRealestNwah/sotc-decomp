float reset_aim_angle_interp_cntrl(char *p, float f)
{
    *(float *)(p + 0xC) = f;
    return f;
}
