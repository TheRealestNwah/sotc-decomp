static float func_00007948(float a)
{
    float r;

    if (a <= 3.14159265f && -3.14159265f <= a) {
        r = a;
    } else {
        r = a - (int)(a / 6.2831853f) * 6.2831853f;
        if (3.14159265f < r)
            r -= 6.2831853f;
        else if (r < -3.14159265f)
            r += 6.2831853f;
    }
    return r;
}
