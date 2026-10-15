void sndSepSetVol(char *s, float v)
{
    int n = (int)(v * 127.0f * *(float *)(s + 0x1C));
    if (n > 127)
        n = 127;
    else if (n < 0)
        n = 0;
    *(short *)(s + 0x28) = n;
}
