extern char padManagerData[];
extern void iosPadGetXZInputR(float *, void *);
void GAMEUTIL_get_1p_right_analog_input(float *x, float *z)
{
    float v[4] __attribute__((aligned(16)));
    iosPadGetXZInputR(v, padManagerData);
    *x=v[0];
    *z=v[2];
}
