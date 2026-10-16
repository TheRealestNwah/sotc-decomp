extern char gcGlobalVar[];

#define MIN_TIME 0.033366699f
#define MAX(a, b) ((a) < (b) ? (b) : (a))

float AI_UpdateVelocity2(float from, float to, float vel, float t)
{
    float g = *(float *)(gcGlobalVar + 0x190);
    float e = from - to;
    float d = to - from;
    float v;
    float acc;
    float t1;
    float t2;

    if (t < g)
        t = g;
    t1 = MAX(t, MIN_TIME);
    v = (e - (from - vel / t1) * 3.0f) * 2.0f / t1;
    t2 = MAX(t, MIN_TIME);
    acc = (d - v * t2) * 2.0f / (t2 * t2);
    return from + acc * 0.5f * g * g + v * g;
}
