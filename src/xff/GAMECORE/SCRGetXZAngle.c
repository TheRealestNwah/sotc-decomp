extern float iosGetATan2fExact(float, float);

float SCRGetXZAngle(float *v)
{
    return iosGetATan2fExact(v[0], v[2]);
}
