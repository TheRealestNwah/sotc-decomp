void GetCrossPositionOf3Plane(float *out, float *a, float *b, float *c)
{
    float A, B, C, D, E, F, ax, inv;

    A = b[1] * c[2] - c[1] * b[2];
    B = b[0] * c[2] - c[0] * b[2];
    C = b[0] * c[1] - c[0] * b[1];
    ax = a[0] * A;
    D = b[3] * c[2] - c[3] * b[2];
    E = b[3] * c[1] - c[3] * b[1];
    F = b[0] * c[3] - c[0] * b[3];
    inv = 1.0f / (ax - a[1] * B + a[2] * C);
    out[0] = (a[1] * D - a[3] * A - a[2] * E) * inv;
    out[1] = (a[3] * B - a[0] * D - a[2] * F) * inv;
    out[2] = (a[1] * F + a[0] * E - a[3] * C) * inv;
    out[3] = 1.0f;
}
