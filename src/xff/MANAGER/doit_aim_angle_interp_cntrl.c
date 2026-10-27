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
