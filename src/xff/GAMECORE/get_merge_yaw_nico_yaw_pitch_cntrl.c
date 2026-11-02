typedef struct {
    char pad0[0x40];
    float add;
    char pad44[0x5C - 0x44];
    float yaw;
    char pad60[0x108 - 0x60];
    int mode0;
    int mode1;
    char pad110[0x114 - 0x110];
    float min;
    float max;
} YawPitchCntrl;

extern float GAMEUTIL_increase_yaw_limit_clip_extend(float, float, float, int, int, int, float, int);
extern float GAMEUTIL_increase_yaw(float, float, int);

float get_merge_yaw_nico_yaw_pitch_cntrl(YawPitchCntrl *c)
{
    int limit;
    if (c->mode0 == 1 || c->mode1 == 1)
        limit = 1;
    else
        limit = 0;
    if (limit == 1)
        return GAMEUTIL_increase_yaw_limit_clip_extend(c->yaw, c->add, c->min, 0, c->mode0, c->mode1, c->max, 0);
    return GAMEUTIL_increase_yaw(c->yaw, c->add, 0);
}
