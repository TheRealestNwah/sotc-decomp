static void func_000C5E40(char *a, char *b)
{
    float d = *(float *)(a + 0x130);

    if (d < *(float *)(b + 0x28))
        *(float *)(a + 0x13C) = d / *(float *)(b + 0x28);
    else if (d < *(float *)(b + 0x2C))
        *(float *)(a + 0x13C) = 1.0f;
    else if (d < *(float *)(b + 0x30))
        *(float *)(a + 0x13C) = (*(float *)(b + 0x30) - d) / (*(float *)(b + 0x30) - *(float *)(b + 0x2C));
    else
        *(float *)(a + 0x13C) = 0.0f;
    *(float *)(a + 0x140) = *(float *)(a + 0x138) * *(float *)(a + 0x13C);
}
