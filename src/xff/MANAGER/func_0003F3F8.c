#ifdef NONMATCHING /* near-miss: register allocation / scheduling differences remain */
typedef struct { char pad[0x10]; float v[5]; } S;

static float func_0003F3F8(S *s, float x, float y, float z)
{
    float a = s->v[0] * 0.0174532925f;
    float b = s->v[1] * 0.0174532925f;
    float d = s->v[3] * 0.0174532925f;
    float e = s->v[4] * 0.0174532925f;
    float c = s->v[2] * 0.0174532925f;
    float r;
    float t;

    if (x < a)
        r = a;
    else
        r = x + b * z;
    t = d;
    if (y < c) {
        float u = y / c;
        t = u * d + (1.0f - u) * e;
    }
    if (t < r)
        r = t;
    return r;
}
#endif
