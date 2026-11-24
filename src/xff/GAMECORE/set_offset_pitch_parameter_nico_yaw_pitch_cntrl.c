extern float GAMEUTIL_increase_pitch(int, int, float, float, float, float);
extern void GAMEUTIL_set_parameter_move_angle(float *, float, float, float, float, float, float);

typedef struct {
    char pad[0xA4];
    float offset;
    float max;
    float min;
    float move[1];
} YawPitchCntrl;

#define PITCH_MAX 1.483529806137085f

void set_offset_pitch_parameter_nico_yaw_pitch_cntrl(YawPitchCntrl *p, float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
    float k = 0.017453293f;
    p->offset = a * k;
    {
        float m = GAMEUTIL_increase_pitch(0, 0, p->offset, b * k, PITCH_MAX, -PITCH_MAX);

        /* Held so the store to max is scheduled after the offset reload. */
        __asm__("" : "+f"(m));
        p->max = m;
    }
    p->min = GAMEUTIL_increase_pitch(0, 0, p->offset, c * k, PITCH_MAX, -PITCH_MAX);
    GAMEUTIL_set_parameter_move_angle(p->move, d, e, f, g, h, i);
}
