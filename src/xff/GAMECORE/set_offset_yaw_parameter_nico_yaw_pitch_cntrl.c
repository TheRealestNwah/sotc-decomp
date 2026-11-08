extern float GAMEUTIL_increase_yaw(int, float, float);
extern void GAMEUTIL_set_parameter_move_angle(float *, float, float, float, float, float, float);

#ifdef NONMATCHING
/* Parked: 13 words differ (register allocation/scheduling); permuter found no zero. */
void set_offset_yaw_parameter_nico_yaw_pitch_cntrl(char *p, float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
    float k = 0.017453293f;
    float t = a * k;
    *(float *)(p + 0x7C) = t;
    *(float *)(p + 0x80) = GAMEUTIL_increase_yaw(0, t, b * k);
    *(float *)(p + 0x84) = GAMEUTIL_increase_yaw(0, *(float *)(p + 0x7C), c * k);
    GAMEUTIL_set_parameter_move_angle((float *)(p + 0x88), d, e, f, g, h, i);
}
#else
void set_offset_yaw_parameter_nico_yaw_pitch_cntrl(char *p, float a, float b, float c, float d, float e, float f, float g, float h, float i);
#endif
