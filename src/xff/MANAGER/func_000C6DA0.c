static float func_000C6DA0(char *p)
{
    float t = *(float *)(p + 0x44);
    if (t < *(float *)(p + 0x58)) {
        return t * *(float *)(p + 0x60);
    }
    if (t < *(float *)(p + 0x5C)) {
        return 1.0f;
    }
    return (*(float *)(p + 0x40) - t) * *(float *)(p + 0x64);
}
