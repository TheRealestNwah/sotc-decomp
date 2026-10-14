typedef struct {
    char pad0[0x90];
    float color[4];
} GlState;

extern GlState D_00130480;

void glColor3fv(float *c)
{
    GlState *gl = &D_00130480;
    float *p;
    int i;

    gl->color[0] = c[0] * 255.0f;
    gl->color[1] = c[1] * 255.0f;
    gl->color[2] = c[2] * 255.0f;
    gl->color[3] = 128.0f;
    p = gl->color;
    for (i = 0; i < 4; i++, p++) {
        if (*p > 255.0f) {
            *p = 255.0f;
        }
        if (*p < 0.0f) {
            *p = 0.0f;
        }
    }
}
