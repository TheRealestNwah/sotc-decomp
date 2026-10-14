float adjustAnglePI(float a)
{
    if (a > 6.2831851f) {
        a -= 6.2831851f;
    } else if (a < -6.2831851f) {
        a += 6.2831851f;
    }
    if (a > 3.1415926f) {
        a += -6.2831851f;
    } else if (a < -3.1415926f) {
        a += 6.2831851f;
    }
    return a;
}
