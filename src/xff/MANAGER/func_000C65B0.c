extern float *D_001370D8;
extern float iosGetRandom(void);

static void func_000C65B0(char *o, char *prm, int flag)
{
    if (0.0f < *D_001370D8 || flag == 1) {
        *(float *)(o + 0x30) = *(float *)(prm + 0x14C) + *(float *)(prm + 0x150) * iosGetRandom();
        *(float *)(o + 0x34) = *(float *)(prm + 0x14C) + *(float *)(prm + 0x150) * iosGetRandom();
        *(float *)(o + 0x3C) = 0.0f;
        *(float *)(o + 0x38) = 0.0f;
    }
}
