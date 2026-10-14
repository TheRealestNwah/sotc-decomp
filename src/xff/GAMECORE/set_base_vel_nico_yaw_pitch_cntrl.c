void set_base_vel_nico_yaw_pitch_cntrl(char *p, float f1, float f2)
{
    *(float *)(p + 0x54) = f1;
    *(float *)(p + 0x60) = f2;
}
