static inline void resetRatio(int *p)
{
    p[2] = 1;
    p[3] = 0;
    if (p[0] == 1)
        *(float *)&p[4] = 0.0f;
    else
        *(float *)&p[4] = 1.0f;
}

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
static inline float distRatio(float value, float low, float high)
{
    float result = 0.0f;
    if (!(value <= low)) {
        result = 1.0f;
        if (!(high <= value))
            result = (value - low) / (high - low);
    }
    return result;
}
float GAMEUTIL_doit_interp_ratio_cntrl(void *input, float delta)
{
    RatioControl *control = input;
    if (control->mode == 1) {
        if (control->time > 0.0f)
            control->started = 0;
        if (delta >= 0.0f)
            control->time += delta;
        else
            control->time += delta * control->backwardScale;
        if (control->clip == 1) {
            if (control->time < 0.0f)
                control->time = 0.0f;
            if (control->time > control->start + control->duration)
                control->time = control->start + control->duration;
        }
        control->ratio = distRatio(control->time, control->start, control->start + control->duration);
        return control->ratio;
    }
    resetRatio((int *)control);
    return control->ratio;
}
