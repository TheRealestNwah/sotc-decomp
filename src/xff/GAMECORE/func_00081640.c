static int func_00081640(float *v)
{
    int ret;

    ret = 0;
    if (v[1] < -10.82f) {
        v[1] = -10.82f;
        ret = 1;
    }
    return ret;
}
