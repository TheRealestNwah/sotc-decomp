#ifdef NONMATCHING
/* Parked: 2 words differ. The volatile load/store force offset to load before the store to max (was 3);
   the original also sets up f14 before that store. */
extern float GAMEUTIL_increase_pitch(int, int, float, float, float, float);
extern void GAMEUTIL_set_parameter_move_angle(float *, float, float, float, float, float, float);

typedef struct {
    char pad[0xA4];
    float offset;
    float max;
    float min;
    float move[1];
} YawPitchCntrl;

void set_offset_pitch_parameter_nico_yaw_pitch_cntrl(YawPitchCntrl *p, float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
    float k = 0.017453293f;
    p->offset = a * k;
    {
        float r = GAMEUTIL_increase_pitch(0, 0, p->offset, b * k, 1.483529806137085f, -1.483529806137085f);
        float o = *(volatile float *)&p->offset;
        *(volatile float *)&p->max = r;
        p->min = GAMEUTIL_increase_pitch(0, 0, o, c * k, 1.483529806137085f, -1.483529806137085f);
    }
    GAMEUTIL_set_parameter_move_angle(p->move, d, e, f, g, h, i);
}
#endif
