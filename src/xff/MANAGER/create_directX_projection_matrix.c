extern float iosGetTanf(float);
extern void iosUnitMatrix(float *);

void create_directX_projection_matrix(float *m, float fov, float aspect, float zNear, float zFar)
{
    float half = fov * 0.5f;
    float sx = 1.0f / iosGetTanf(half * aspect * 0.0174532925f);
    float sy = 1.0f / iosGetTanf(half * 0.0174532925f);
    float q = zFar / (zFar - zNear);

    iosUnitMatrix(m);
    m[0] = sx;
    m[5] = sy;
    m[11] = 1.0f;
    m[15] = 0.0f;
    m[10] = q;
    m[14] = -q * zNear;
}
