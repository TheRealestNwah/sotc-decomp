extern float GAMEUTIL_increase_yaw(int, float, float);
extern void GAMEUTIL_set_parameter_move_angle(void *, float, float, float, float, float, float);

void set_offset_yaw_parameter_nico_yaw_pitch_cntrl(char *c, float base, float min, float max,
                                                   float a, float b, float d, float e, float f, float g)
{
    *(float *)(c + 0x7C) = base * 0.017453293f;
    *(float *)(c + 0x80) = GAMEUTIL_increase_yaw(0, *(float *)(c + 0x7C), min * 0.017453293f);
    *(float *)(c + 0x84) = GAMEUTIL_increase_yaw(0, *(float *)(c + 0x7C), max * 0.017453293f);
    GAMEUTIL_set_parameter_move_angle(c + 0x88, a, b, d, e, f, g);
}
