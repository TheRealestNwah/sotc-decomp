void set_base_yaw_parameter_nico_yaw_pitch_cntrl(char *p, int mode, float a, float b, float c, float d, float e, float f)
{
    float k = 0.0174532925f;
    *(int *)(p + 0xCC) = mode;
    *(float *)(p + 0xD0) = a * k;
    *(float *)(p + 0xD4) = b * k;
    *(float *)(p + 0xD8) = c * k;
    *(float *)(p + 0xDC) = d * k;
    *(float *)(p + 0xE0) = e * k;
    *(float *)(p + 0xE4) = f;
}
