static void func_00052170(char *c, float dt)
{
    int mode = *(int *)(c + 0xC90);
    char *m;
    float min;
    float max;

    if (mode == 0)
        return;
    if (*(signed char *)(c + 0x5E2) != 0) {
        m = c + 0x1C0;
        min = *(float *)(c + 0x5C8);
        max = *(float *)(c + 0x5C4);
        switch (mode) {
        case 1:
            *(float *)(m + 0x1C) += (max - min) * dt / *(float *)(c + 0x5CC) * *(float *)(c + 0x5E4);
            if (max < *(float *)(m + 0x1C))
                *(float *)(m + 0x1C) = max;
            break;
        case -1:
            *(float *)(m + 0x1C) -= (max - min) * dt / *(float *)(c + 0x5D0) * *(float *)(c + 0x5E4);
            if (*(float *)(m + 0x1C) < min)
                *(float *)(m + 0x1C) = min;
            break;
        case -2:
            *(float *)(m + 0x1C) -= (max - min) * dt / *(float *)(c + 0x5D4) * *(float *)(c + 0x5E4);
            if (*(float *)(m + 0x1C) < min)
                *(float *)(m + 0x1C) = min;
            break;
        }
        if (*(float *)(c + 0x5D8) >= *(float *)(m + 0x1C))
            *(signed char *)(c + 0x5E0) = 1;
        if (*(float *)(c + 0x5DC) <= *(float *)(m + 0x1C))
            *(signed char *)(c + 0x5E1) = 1;
    }
    *(int *)(c + 0xC90) = 0;
}
