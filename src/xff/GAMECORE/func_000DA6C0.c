static float func_000DA6C0(float ref, float val, float step)
{
    float q;
    float base;
    float ret;
    int n;

    ret = val;
    if (step != 0.0f) {
        q = ref / step;
        n = q;
        if (q - (float)n <= 0.5f) {
            base = step * (float)n;
        } else {
            base = step * (float)(n + 1);
        }
        ret = base + (float)(int)((val - base) / step) * step;
    }
    return ret;
}
