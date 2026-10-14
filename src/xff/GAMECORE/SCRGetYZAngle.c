extern float iosGetATan2fExact(float, float);

float SCRGetYZAngle(float *v)
{
    return iosGetATan2fExact(v[1], v[2]);
}
