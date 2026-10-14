int chkMoveAngle2(float a, float b)
{
    if (__builtin_fabsf(a + b) <= 0.0174532925f) {
        return 1;
    }
    return 0;
}
