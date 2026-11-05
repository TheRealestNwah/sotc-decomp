extern float D_00139F54;
extern float D_00139F58;

extern float iosGetTanf(float x);
extern void iosUnitMatrix(void *m);

void create_original_clip_matrix(float *m, float angle, float width, float near, float far)
{
    int w;
    float d;
    float sx;
    float sy;

    w = width * 1000.0f;
    d = 500.0f / iosGetTanf(angle * 0.5f * 0.017453293f) / D_00139F54;
    sx = d / ((float)w * 0.5f);
    sy = d / 500.0f * D_00139F54 / 0.90909f / D_00139F58;
    iosUnitMatrix(m);
    m[0] = sx;
    m[5] = sy;
    m[10] = (far + near) / (far - near);
    m[11] = 1.0f;
    m[14] = far * near * -2.0f / (far - near);
    m[15] = 0.0f;
}
