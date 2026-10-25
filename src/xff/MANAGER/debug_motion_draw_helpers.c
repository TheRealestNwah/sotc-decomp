extern void *memset(void *, int, unsigned int);
extern void glColor4f(float, float, float, float);
extern void iosGetCurrentMatrix(void *);
extern void iosScaleMatrixV(void *, void *, void *);
extern void glLoadMatrixf(int);
extern void *iosgluGetCameraContext(void);
extern float GetScreenRadius(void *, void *, float);
extern void iosgluDrawObject(void *);
extern void *B_00148A10[];

static float func_00037088(int primitive, int mode, float radius, float length)
{
    float scale[4] __attribute__((aligned(16)));
    float matrix[16] __attribute__((aligned(16)));
    memset(scale, 0, sizeof(scale));
    scale[2] = length;
    scale[0] = radius;
    scale[1] = radius;
    if (primitive == 2) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.1f);
    } else if (mode != 0) {
        glColor4f(0.0f, 0.2f, 0.5f, 1.0f);
    } else {
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    }
    iosGetCurrentMatrix(matrix);
    iosScaleMatrixV(matrix, matrix, scale);
    glLoadMatrixf((int)matrix);
    return GetScreenRadius(iosgluGetCameraContext(), matrix + 12, radius);
}

static int func_0003DB20(int primitive, int mode, float radius, float length)
{
    int drawn = 0;
    if (func_00037088(primitive, mode, radius, length) > 1.0f) {
        iosgluDrawObject(B_00148A10[primitive]);
        drawn = 1;
    }
    return drawn;
}
