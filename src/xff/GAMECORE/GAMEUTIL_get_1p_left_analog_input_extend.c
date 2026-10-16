extern char padManagerData[];
extern void iosPadGetXZInputLwithThreshold(float *, void *);
extern void iosPadGetXZInputLwithThresholdIndepAxis(float *, void *);

void GAMEUTIL_get_1p_left_analog_input_extend(float *x, float *z, int mode)
{
    float v[4];

    if (mode == 1)
        iosPadGetXZInputLwithThreshold(v, padManagerData);
    else
        iosPadGetXZInputLwithThresholdIndepAxis(v, padManagerData);
    *x = v[0];
    *z = v[2];
}
