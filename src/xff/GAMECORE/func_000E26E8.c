extern float GAMEUTIL_get_dist_ratio(float, float, float);

static void func_000E26E8(float *a, float *b, float *v, char **pp, float fa, float fb)
{
    char *p = *pp;
    float xz;
    float y;
    register float zero __asm__("$f1") = 0.0f;

    if (*(float *)(p + 0x68) > zero && *(float *)(p + 0x80) > zero) {
        float z = zero;
        do {
            {
                register float zz __asm__("$f1") = v[2] * v[2];
                xz = v[0] * v[0] + zz;
            }
            y = v[1] * v[1];
            if (xz > z || y > z) {
                if (y < xz) {
                    *b = GAMEUTIL_get_dist_ratio(y / xz, 0.5f, 1.0f) * fb;
                } else {
                    *a = GAMEUTIL_get_dist_ratio(xz / y, 0.5f, 1.0f) * fa;
                }
            }
        } while (0);
    }
}
