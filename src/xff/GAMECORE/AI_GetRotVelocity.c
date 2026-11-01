extern char gcGlobalVar[];
extern float AI_GetInterRatio(float, float, float, float, float);

#define MAX(a, b) ((a) < (b) ? (b) : (a))

float AI_GetRotVelocity(float cur, float diff, float c, float d)
{
    float t = AI_GetInterRatio(diff < 0.0f ? -diff : diff, 3.1415926f, 0.0f, c, d);
    float dt = *(float *)(gcGlobalVar + 0x190);
    float T, v, acc, target;

    if (t < dt)
        t = dt;
    T = t;
    target = 0.0f;
    if (T < dt)
        T = dt;
    {
        float T1 = MAX(T, 0.033366699f);
        v = ((cur - target) - (cur - diff / T1) * 3.0f) * 2.0f / T1;
    }
    {
        float T2 = MAX(T, 0.033366699f);
        acc = ((target - cur) - v * T2) * 2.0f / (T2 * T2);
    }
    return cur + acc * 0.5f * dt * dt + v * dt;
}
