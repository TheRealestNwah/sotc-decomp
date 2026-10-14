typedef struct {
    char pad0[0x130];
    float x[4];
    float y[4];
    float z[4];
} GlState;

extern GlState D_00130480;

void glLightVector(float *v, int light)
{
    GlState *gl = &D_00130480;

    v[0] = gl->x[light];
    v[1] = gl->y[light];
    v[2] = gl->z[light];
}
