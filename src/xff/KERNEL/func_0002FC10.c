extern float sinf(float);
extern float cosf(float);
extern float powf(float, float);

static void func_0002FC10(char *p)
{
    float a = powf(10.0f, *(float *)(p + 0x2C) / 40.0f);
    float w = *(float *)(p + 0x30) / 48000.0f * 2.0f * 3.14159265358979f;
    float alpha = sinf(w) / 6.0f;

    *(float *)(p + 0x10) = 1.0f + alpha * a;
    *(float *)(p + 0x14) = cosf(w) * -2.0f;
    *(float *)(p + 0x18) = 1.0f - alpha * a;
    *(float *)(p + 0x4) = 1.0f + alpha / a;
    *(float *)(p + 0x8) = cosf(w) * -2.0f;
    *(float *)(p + 0xC) = 1.0f - alpha / a;
}
