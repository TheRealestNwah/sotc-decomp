static void func_000CAA40(float *left, float *right, float blend)
{
    if (blend < 0.0f) {
        *left = blend + 1.0f;
        *right = 0.0f;
    } else if (blend < 1.0f) {
        *left = 1.0f - blend;
        *right = blend;
    } else {
        *left = 0.0f;
        *right = blend;
    }
}
