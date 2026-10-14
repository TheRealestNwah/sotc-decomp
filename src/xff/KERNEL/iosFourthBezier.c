float iosFourthBezier(void *arg0, float fparg0)
{
    float temp_f0;
    float temp_f4;
    float temp_f6;

    temp_f6 = fparg0 * fparg0;
    temp_f4 = 1.0f - fparg0;
    temp_f0 = temp_f4 * temp_f4;
    return (temp_f0 * temp_f4 * (*(float *)((char *)(arg0) + 0))) + (temp_f0 * 3.0f * fparg0 * (*(float *)((char *)(arg0) + 4))) + (temp_f4 * 3.0f * temp_f6 * (*(float *)((char *)(arg0) + 8))) + (temp_f6 * fparg0 * (*(float *)((char *)(arg0) + 0xC)));
}
