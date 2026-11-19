typedef struct {
    int mode;
    float rate, maximum, current;
} AimAngleControl;
static float func_000097E0(int, float, float, float, float, float, float);
static float func_000099A0(float, float, float, float, float, float);
float doit_aim_angle_interp_cntrl(AimAngleControl *state, int force,
                                  float target, float delta, float parameter)
{
    if (force == 1 || state->rate < 0.0f || state->maximum < 0.0f) {
        state->current = target;
    } else {
        switch ((unsigned int)state->mode) {
        case 0:
        case 1:
            state->current = func_000097E0(state->mode, state->current, target,
                delta, state->rate, state->maximum, parameter);
            break;
        case 2:
            state->current = func_000099A0(state->current, target, delta,
                state->rate, state->maximum, parameter);
            break;
        }
    }
    return state->current;
}

/* Parked draft: eases an aim yaw towards the target, with the step scaled by rate * parameter and
   the result clamped to maximum * parameter. 21 diffs, same size. Register pins put diff, v and step
   where the Original has them; left: -diff is computed into the copy rather than into step, and
   step * |diff / step| is written straight into step instead of through a temporary (one word
   longer in the Original, which shifts the later branch offsets). */
#ifdef NONMATCHING
extern float GAMEUTIL_get_move_radi_from_yaw1_to_yaw2_extend(int, int, float, float);
extern int GAMEUTIL_is_nearly_equal_zero(float, float);
extern float GAMEUTIL_increase_yaw(int, float, float);
extern int GAMEUTIL_is_reach_aim_yaw_angle(float *out, float a, float b, float aim);
static float func_000097E0(int mode, float cur, float target, float delta, float rate, float maximum, float parameter)
{
    float out = cur;
    register float diff __asm__("$f20") = 0.0f;
    register float v __asm__("$f21") = diff;
    float d, a, nd;
    register float step __asm__("$f12");
    d = 0.0f - GAMEUTIL_get_move_radi_from_yaw1_to_yaw2_extend(0, mode == 1, cur, target);
    nd = -diff;
    if (diff < d) diff = d - diff;
    else if (d < nd) diff = d - nd;
    if (!GAMEUTIL_is_nearly_equal_zero(diff, 0.0001f)) {
        step = -diff;
        if (0.0f <= rate) step = step * (rate * parameter);
        a = step;
        if (step < 0.0f) a = -step;
        if (diff < 0.0f ? -diff < a : diff < a) {
            if (step != 0.0f) {
                a = diff / step;
                if (a < 0.0f) a = -a;
                step = step * a;
            }
        }
        v += step;
    }
    if (0.0f < maximum) {
        float lim = maximum * parameter;
        if (0.0f <= v) {
            if (lim < v) v = lim;
        } else if (lim < -v) v = -lim;
    }
    out = GAMEUTIL_increase_yaw(0, cur, v);
    GAMEUTIL_is_reach_aim_yaw_angle(&out, cur, out, target);
    return out;
}
#endif

/* Parked draft: the pitch counterpart of func_000097E0, clamped to +-85 degrees by
   GAMEUTIL_near_to_aim_pitch_angle. 21 diffs, same size. Left: the same -diff/step copy order and
   step * |diff / step| temporary as func_000097E0, and -0.0f is negated from v's copy instead of
   from the zero constant. */
#ifdef NONMATCHING
extern float GAMEUTIL_get_difference_pitch_and_pitch(float, float);
extern int GAMEUTIL_near_to_aim_pitch_angle(float *out, int, int, float, float, float, float, float);
static float func_000099A0(float cur, float target, float delta, float rate, float maximum, float parameter)
{
    float out = cur;
    float v, diff, d, a, nd;
    register float step __asm__("$f12");
    d = 0.0f - GAMEUTIL_get_difference_pitch_and_pitch(cur, target);
    v = 0.0f;
    nd = -v;
    if (v < d) diff = d - v;
    else if (d < nd) diff = d - nd;
    else diff = v;
    if (!GAMEUTIL_is_nearly_equal_zero(diff, 0.0001f)) {
        step = -diff;
        if (0.0f <= rate) step = step * (rate * parameter);
        a = step;
        if (step < 0.0f) a = -step;
        if (diff < 0.0f ? -diff < a : diff < a) {
            if (step != 0.0f) {
                a = diff / step;
                if (a < 0.0f) a = -a;
                step = step * a;
            }
        }
        v += step;
    }
    if (0.0f < maximum) {
        float lim = maximum * parameter;
        if (0.0f <= v) {
            if (lim < v) v = lim;
        } else if (lim < -v) v = -lim;
    }
    GAMEUTIL_near_to_aim_pitch_angle(&out, 0, 0, cur, v, target, 1.48352981f, -1.48352981f);
    return out;
}
#endif
