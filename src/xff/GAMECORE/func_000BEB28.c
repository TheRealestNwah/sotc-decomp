/* Parked attempt: 4 words differ from the Original. */
#ifdef NONMATCHING
typedef struct {
    int active;
    float period;
    float amp;
    float pad;
    float start;
    float out;
} LifebarWave;

extern LifebarWave B_0019CD10;
extern LifebarWave B_0019CD28;
extern unsigned char gcGlobalVar[];
extern void func_000BC988(int);
extern float iosGetSinf(float);
extern void func_000BE838(float);

static inline float lifebarWaveCalc(LifebarWave *w)
{
    float out = 0.0f;
    float t;

    if (w->active != 0) {
        t = *(float *)(gcGlobalVar + 0x178) - w->start;
        if (w->period <= t) {
            w->active = 0;
        } else {
            func_000BC988(4);
            out = w->amp * iosGetSinf(t * 3.14159265f / w->period);
        }
    }
    return out;
}

static void func_000BEB28(float dt)
{
    B_0019CD10.out = lifebarWaveCalc(&B_0019CD10);
    B_0019CD28.out = lifebarWaveCalc(&B_0019CD28);
    func_000BE838(dt);
}
#endif
