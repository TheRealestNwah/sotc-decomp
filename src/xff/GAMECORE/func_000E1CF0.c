typedef struct { int x0; float x4; float x8; } S;
typedef struct { char pad[0x1834]; int x1834; } G;
static void func_000E1CF0(S *s, G *g, float dt)
{
    float v;
    if (s->x0 == 0 || g->x1834 == 1) {
        v = s->x8 - dt * 0.5f;
        s->x8 = v;
        if (v < 0.0f) s->x8 = 0.0f;
    } else {
        s->x4 = 1.0f;
        s->x8 = s->x8 + dt;
    }
}
