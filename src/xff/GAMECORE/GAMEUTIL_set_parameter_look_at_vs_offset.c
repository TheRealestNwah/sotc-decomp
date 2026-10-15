void GAMEUTIL_set_parameter_look_at_vs_offset(char *p, float yaw, float pitch, float roll, float dist, float height)
{
    *(float *)(p + 0x3C) = yaw * 0.017453293f;
    *(float *)(p + 0x40) = pitch * 0.017453293f;
    *(float *)(p + 0x44) = roll * 0.017453293f;
    *(float *)(p + 0x48) = dist;
    *(float *)(p + 0x4C) = height;
}
