static inline int is_between(float value, float first, float second)
{
    if (((first <= value) && (value <= second)) || ((second <= value) && (value <= first))) {
        return 1;
    }
    return 0;
}

static inline int is_nearly_zero(float x, float eps)
{
    if (x < 0.0f) {
        if (-x <= eps) {
            goto yes;
        } else {
            goto no;
        }
    } else {
        if (x <= eps) {
            goto yes;
        } else {
            goto no;
        }
    }
yes:
    return 1;
no:
    return 0;
}
static inline int reaches_pitch(float from, float next, float aim, float *out)
{
    int reached;
    float delta;
    reached = is_between(aim, from, next);
    if (reached != 1) {
        delta = aim - next;
        if (delta < 0.0f) {
            delta = -delta;
        }
        reached = is_nearly_zero(delta, 0.0001f);
    }
    if (reached == 1) {
        if (out != 0) {
            *out = aim;
        }
        return 1;
    }
    if (out != 0) {
        *out = next;
    }
    return 0;
}


extern int GAMEUTIL_inc_or_dec_for_near_to_aim_pitch(float *, int, float, float, float, float, float);

int GAMEUTIL_near_to_aim_pitch_angle(float *out, int *direction, int clip,
                                    float from, float step, float aim, float high, float low)
{
    int result = GAMEUTIL_inc_or_dec_for_near_to_aim_pitch(out, clip, from, step, aim, high, low);

    if (direction != 0) {
        *direction = result;
    }
    return reaches_pitch(from, *out, aim, out);
}
