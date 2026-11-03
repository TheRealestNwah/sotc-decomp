#define fabsf __builtin_fabsf

static int func_001073E0(char *p, int flag)
{
    char *c = *(char **)(p + 0xCC);

    if (*(int *)(c + 0x34) != 0) {
        if (*(int *)(p + 0xC4) != 0 && *(float *)(c + 0x78) * 0.5f < fabsf(*(float *)(p + 0x130)))
            return 0;
        if (*(int *)(p + 0xC8) != 0 && *(float *)(p + 0x13C) / *(float *)(c + 0xC4) < 1.0f
            && *(float *)(c + 0x78) * 0.5f < fabsf(*(float *)(p + 0x134)))
            return 0;
        if (flag == 0)
            return 1;
        if (*(int *)(c + 0x30) == 0)
            return 1;
        if (*(float *)(p + 0x13C) / *(float *)(c + 0xC4) > fabsf(*(float *)(p + 0x130)) / *(float *)(c + 0x78))
            return 1;
    }
    return 0;
}
