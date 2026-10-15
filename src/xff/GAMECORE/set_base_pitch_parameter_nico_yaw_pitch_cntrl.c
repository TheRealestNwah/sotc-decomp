void set_base_pitch_parameter_nico_yaw_pitch_cntrl(char *p, int mode, float a, float b, float c, float d, float e, float f)
{
    float k = 0.0174532925f;
    *(int *)(p + 0xE8) = mode;
    *(float *)(p + 0xEC) = a * k;
    *(float *)(p + 0xF0) = b * k;
    *(float *)(p + 0xF4) = c * k;
    *(float *)(p + 0xF8) = d * k;
    *(float *)(p + 0xFC) = e * k;
    *(float *)(p + 0x100) = f;
}
