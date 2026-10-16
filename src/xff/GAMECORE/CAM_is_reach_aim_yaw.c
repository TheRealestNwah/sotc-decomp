int CAM_is_reach_aim_yaw(float *out, int dir, float a, float b, float c, float d)
{
    int r = 0;
    float t;

    if (a == d || c == d) {
        c = d;
        r = 1;
    } else if (dir == 1) {
        t = d;
        if (d < a)
            t = d + 6.283185307179586f;
        if (t < a + b) {
            c = d;
            r = 1;
        }
    } else if (dir == -1) {
        t = d;
        if (a < d)
            t = d - 6.283185307179586f;
        if (a - b < t) {
            c = d;
            r = 1;
        }
    }
    if (out != 0)
        *out = c;
    return r;
}
