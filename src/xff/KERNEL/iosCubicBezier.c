float iosCubicBezier(void *arg0, float fparg0)
{
    float temp_f0;

    temp_f0 = 1.0f - fparg0;
    return (temp_f0 * temp_f0 * (*(float *)((char *)(arg0) + 0))) + (2.0f * temp_f0 * fparg0 * (*(float *)((char *)(arg0) + 4))) + (fparg0 * fparg0 * (*(float *)((char *)(arg0) + 8)));
}
