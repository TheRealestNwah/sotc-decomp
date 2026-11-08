extern int D_000409D4;
extern float B_00054C00[];
extern float sinf(float);
extern float cosf(float);
extern float sqrtf(float);

void InitTableSinCos(void)
{
    int i;
    if (D_000409D4 == 0) {
        for (i = 0; i <= 0x4000; i++) {
            float x = i * (1.0f / 16384.0f);
            if (x > 0.5f) {
                float s = sinf(x * 1.5707963f);
                B_00054C00[i] = sqrtf(1.0f - s * s);
            } else {
                B_00054C00[i] = cosf(x * 1.5707963f);
            }
        }
        D_000409D4 = 1;
    }
}
