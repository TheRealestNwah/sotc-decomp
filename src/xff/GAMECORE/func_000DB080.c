extern float GAMEUTIL_get_difference_yaw_and_yaw(float, float);
extern float GAMEUTIL_get_difference_pitch_and_pitch(float, float);

typedef struct {
    int mode;
    char p4[0x1C];
    float yaw;
    float pitch;
} Aim;

typedef struct {
    char p0[0x30];
    float yaw;
    float pitch;
} Dir;

static int func_000DB080(Aim *a, char *b)
{
    Dir *d;

    if (a->mode != 0) {
        d = (Dir *)(b + 0x60);
        if (a->mode == 1) {
            if (GAMEUTIL_get_difference_yaw_and_yaw(d->yaw, a->yaw) <= 0.034906585f) {
                return 1;
            }
        } else if (GAMEUTIL_get_difference_yaw_and_yaw(d->yaw, a->yaw) <= 0.034906585f
                   && GAMEUTIL_get_difference_pitch_and_pitch(d->pitch, a->pitch) <= 0.034906585f) {
            return 1;
        }
    }
    return 0;
}
