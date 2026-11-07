typedef struct {
    char pad[0x10];
    float v[5];
} NeckLimit;

static float func_0003F3F8(NeckLimit *l, float x, float y, float z)
{
    float a = l->v[0] * 0.0174532925f;
    float b = l->v[1] * 0.0174532925f;
    float c = l->v[2] * 0.0174532925f;
    float d = l->v[3] * 0.0174532925f;
    float e = l->v[4] * 0.0174532925f;
    float r, t;

    t = d;
    if (x < a)
        r = a;
    else
        r = x + b * z;
    if (y < c) {
        float u = y / c;
        t = u * d + (1.0f - u) * e;
    }
    if (t < r)
        r = t;
    return r;
}
