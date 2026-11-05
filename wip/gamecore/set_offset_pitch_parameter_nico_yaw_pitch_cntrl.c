extern float GAMEUTIL_increase_pitch(int, int, float, float, float, float);
extern void GAMEUTIL_set_parameter_move_angle(void *, float, float, float, float, float, float);

typedef struct {
    char pad[0xA4];
    float base;
    float min;
    float max;
    char move[1];
} PitchCntrl;

void set_offset_pitch_parameter_nico_yaw_pitch_cntrl(PitchCntrl *c, float base, float min, float max,
                                                     float a, float b, float d, float e, float f, float g)
{
    c->base = base * 0.017453293f;
    c->min = GAMEUTIL_increase_pitch(0, 0, c->base, min * 0.017453293f, 1.483529806137085f, -1.483529806137085f);
    c->max = GAMEUTIL_increase_pitch(0, 0, c->base, max * 0.017453293f, 1.483529806137085f, -1.483529806137085f);
    GAMEUTIL_set_parameter_move_angle(c->move, a, b, d, e, f, g);
}
