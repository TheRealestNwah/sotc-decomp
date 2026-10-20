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
static int func_000096E8(RatioControl *, float, float);
extern void func_00009730(void *, int);
void GAMEUTIL_set_param_interp_ratio_cntrl(char *input, float start, float duration)
{
    RatioControl *control = (void *)input;
    int changed;
    if (start < 0.0f)
        start = 0.0f;
    changed = func_000096E8(control, start, duration);
    control->start = start;
    control->duration = duration;
    control->backwardScale = 1.0f;
    func_00009730(control, changed);
}
static int func_000096E8(RatioControl *control, float start, float duration)
{
    if (control->time > 0.0f &&
        (control->start != start || control->duration != duration))
        return 1;
    return 0;
}
