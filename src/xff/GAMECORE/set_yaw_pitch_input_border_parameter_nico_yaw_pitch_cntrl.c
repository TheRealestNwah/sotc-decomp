void set_yaw_pitch_input_border_parameter_nico_yaw_pitch_cntrl(char *p, float f1, float f2, float f3, float f4)
{
    *(float *)(p + 0x6C) = f1;
    *(float *)(p + 0x70) = f2;
    *(float *)(p + 0x74) = f3;
    *(float *)(p + 0x78) = f4;
}
