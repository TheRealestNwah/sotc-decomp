extern void iosGetExceptAxisVector(float *, float *, float *);
void GAMEUTIL_get_except_axis_vector(float *out, float *value, float *axis)
{
    iosGetExceptAxisVector(out, value, axis);
}
