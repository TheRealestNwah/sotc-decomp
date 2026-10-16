extern float GAMEUTIL_increase_yaw(int, float, float);

void set_max_min_yaw_parameter_nico_yaw_pitch_cntrl(char *c, int a, int b, int d, float base, float max, float min)
{
    *(int *)(c + 0x104) = a;
    *(int *)(c + 0x108) = b;
    *(int *)(c + 0x10C) = d;
    *(float *)(c + 0x110) = base * 0.017453293f;
    if (89.0f < max)
        max = 89.0f;
    if (min < -89.0f)
        min = -89.0f;
    *(float *)(c + 0x114) = GAMEUTIL_increase_yaw(0, *(float *)(c + 0x110), max * 0.017453293f);
    *(float *)(c + 0x118) = GAMEUTIL_increase_yaw(0, *(float *)(c + 0x110), min * 0.017453293f);
}
