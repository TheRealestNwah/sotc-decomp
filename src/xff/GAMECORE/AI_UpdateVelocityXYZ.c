typedef struct {
    char pad0[0x190];
    float speed;
} GlobalVar;

extern GlobalVar gcGlobalVar;

static inline void approach(float *v, float t, float a)
{
    float x = *v;

    if (x < t) {
        x += a * gcGlobalVar.speed;
        if (t < x)
            x = t;
    } else {
        x -= a * gcGlobalVar.speed;
        if (x < t)
            x = t;
    }
    *v = x;
}

void AI_UpdateVelocityXYZ(float *v, float *t, float *a)
{
    approach(&v[0], t[0], a[0]);
    approach(&v[1], t[1], a[1]);
    approach(&v[2], t[2], a[2]);
}
