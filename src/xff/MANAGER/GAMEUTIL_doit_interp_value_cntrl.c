typedef struct {
    float start;
    float value;
    float hope;
} InterpValueCntrl;
typedef struct {
    int mode;
    int clip;
    int started;
    float time;
    float ratio;
    float start;
    float duration;
    float backwardScale;
} RatioControl;
extern float GAMEUTIL_get_interp_value_interp_value_cntrl(void *);
static inline float resetValue(InterpValueCntrl *cntrl, float value)
{
    cntrl->start = value;
    cntrl->value = value;
    cntrl->hope = value;
    return GAMEUTIL_get_interp_value_interp_value_cntrl(cntrl);
}
static inline float interpolate(float a, float b, float t)
{
    if (t <= 0.0f) return b;
    if (t >= 1.0f) return a;
    if (a == b) return a;
    return (t * a) + ((1.0f - t) * b);
}
float GAMEUTIL_doit_interp_value_cntrl(void *input, void *ratioInput, float target)
{
    InterpValueCntrl *value = input;
    RatioControl *ratio = ratioInput;
    if (ratio->mode == 1) {
        if (ratio->started == 1)
            value->start = value->value;
        value->hope = target;
        value->value = interpolate(target, value->start, ratio->ratio);
    } else
        resetValue(value, target);
    return GAMEUTIL_get_interp_value_interp_value_cntrl(value);
}
