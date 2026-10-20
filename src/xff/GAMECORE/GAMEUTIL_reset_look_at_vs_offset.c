typedef struct {
    float current;
    float target;
    float velocity;
    float ratio;
    int changedSide;
    int active;
    int mode;
    char interpolation[0x20];
} LookAtOffset;
extern void GAMEUTIL_reset_interp_ratio_cntrl(void *);
extern void GAMEUTIL_set_param_interp_ratio_cntrl(void *, float, float);
static inline int crossedZero(float oldValue, float newValue)
{
    if (oldValue != newValue)
        return oldValue * newValue <= 0.0f;
    return 0;
}
static inline void setOffset(LookAtOffset *offset, float value)
{
    if (crossedZero(offset->current, value))
        offset->changedSide = 1;
    else
        offset->changedSide = 0;
    offset->current = value;
}
void GAMEUTIL_reset_look_at_vs_offset(LookAtOffset *offset)
{
    setOffset(offset, 0.0f);
    offset->ratio = 1.0f;
    offset->target = 0.0f;
    offset->velocity = 0.0f;
    offset->active = 0;
    GAMEUTIL_reset_interp_ratio_cntrl(offset->interpolation);
    GAMEUTIL_set_param_interp_ratio_cntrl(offset->interpolation, 0.0f, 1.0f);
}
