extern int GAMEUTIL_is_nearly_equal_zero(float, float);

static int func_000ECE28(float *out, int n, float *keys, float *vals, float def)
{
    float best = keys[0];
    int i;

    *out = vals[0];
    for (i = 1; i < n; i++) {
        if (best < keys[i]) {
            best = keys[i];
            *out = vals[i];
        }
    }
    if (GAMEUTIL_is_nearly_equal_zero(best, 0.0001f) == 1) {
        *out = def;
        return 0;
    }
    return 1;
}
