extern float sinf(float);
extern float cosf(float);

static void func_0002FA10(char *p)
{
    float w = *(float *)(p + 0x30) / 48000.0f * 2.0f * 3.14159265358979f;
    float alpha;

    alpha = sinf(w) / 6.0f;
    *(float *)(p + 0x10) = (1.0f - cosf(w)) * 0.5f;
    *(float *)(p + 0x14) = 1.0f - cosf(w);
    *(float *)(p + 0x18) = (1.0f - cosf(w)) * 0.5f;
    *(float *)(p + 0x4) = alpha + 1.0f;
    *(float *)(p + 0x8) = cosf(w) * -2.0f;
    *(float *)(p + 0xC) = 1.0f - alpha;
}
