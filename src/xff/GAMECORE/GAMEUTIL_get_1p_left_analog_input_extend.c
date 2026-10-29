extern char padManagerData[];
extern void iosPadGetXZInputLwithThreshold(float *, void *, float);
extern void iosPadGetXZInputLwithThresholdIndepAxis(float *, void *, float);

void GAMEUTIL_get_1p_left_analog_input_extend(float *x, float *z, int mode, float threshold)
{
    float v[4];

    if (mode == 1)
        iosPadGetXZInputLwithThreshold(v, padManagerData, threshold);
    else
        iosPadGetXZInputLwithThresholdIndepAxis(v, padManagerData, threshold);
    *x = v[0];
    *z = v[2];
}
