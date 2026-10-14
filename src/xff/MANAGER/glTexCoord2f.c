typedef struct {
    char pad0[0xA0];
    float s;
    float t;
    float r;
    int q;
} GlState;

extern GlState D_00130480;

void glTexCoord2f(float s, float t)
{
    GlState *gl = &D_00130480;

    gl->s = s;
    gl->t = t;
    gl->r = 1.0f;
    gl->q = 0;
}
