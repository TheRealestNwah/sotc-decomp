extern unsigned char B_0014E898[1];

void adpcmCloseFadeSetVol(int arg0, float fparg0)
{
    void *temp_a0;

    temp_a0 = &B_0014E898 + (arg0 * 0x560);
    if ((*(float *)((char *)(temp_a0) + 0x4C)) != 0.0f) {
        (*(float *)((char *)(temp_a0) + 0x50)) = fparg0;
    }
}
